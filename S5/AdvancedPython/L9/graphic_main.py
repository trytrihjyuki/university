import db_engine as db
import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

class ListBoxRowWithData(Gtk.ListBoxRow):
    def __init__(self, printable_data, full_data):
        super().__init__()
        self.printable_data = printable_data
        self.full_data = full_data
        self.add(Gtk.Label(label=printable_data))

class App(Gtk.Window):
    def __init__(self):
        super(App, self).__init__()
        self.columns = ['id', 'author_first_name', 'author_last_name', 'title', 'year']
        self.set_border_width(10)
        self.box_outer = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=6)
        self.add(self.box_outer)

        # add buttons to app
        self.button_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=5)
        self.add_buttons(self.button_box)
        self.box_outer.pack_start(self.button_box, True, True, 0)
        self.turn_action_btns(False)

        # row description
        self.label_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=5)
        self.label = Gtk.Label()
        self.box_outer.pack_start(self.label, True, True, 0)

        # create listbox for rows
        if hasattr(self, 'session'):
            self.refresh_rows()

        self.connect("destroy", Gtk.main_quit)
        self.set_size_request(450,350)
        self.show()

    def add_buttons(self, box):
        self.add_btn = Gtk.Button.new_with_label("Add")
        self.add_btn.connect("clicked", self.create_popup, self.columns[1:], 'Add')
        self.modify_btn = Gtk.Button.new_with_label("Modify")
        self.modify_btn.connect("clicked", self.create_popup, self.columns[1:], 'Modify')
        self.delete_btn = Gtk.Button.new_with_label("Delete")
        self.delete_btn.connect("clicked", self.create_popup, self.columns[1:], 'Delete')
        load_btn = Gtk.Button.new_with_label("Load db")
        load_btn.connect("clicked", self.choose_popup, True)
        save_btn = Gtk.Button.new_with_label("Save db")
        save_btn.connect("clicked", self.choose_popup, False)

        box.pack_start(self.add_btn, True, True, 0)
        box.pack_start(self.modify_btn, True, True, 0)
        box.pack_start(self.delete_btn, True, True, 0)
        box.pack_start(load_btn, True, True, 0)
        box.pack_start(save_btn, True, True, 0)

    def turn_action_btns(self, on):
        self.add_btn.set_sensitive(on)
        self.modify_btn.set_sensitive(on)
        self.delete_btn.set_sensitive(on)

    def add_rows(self):
        for pr, fr in zip(self.printable_rows, self.full_rows):
            row = ListBoxRowWithData(pr, fr)
            self.rows_box.add(row)
            self.rows_box.connect('row-selected', self.update_row_desc)
        self.box_outer.pack_start(self.rows_box, True, True, 0)

    def update_row_desc(self, lb, row, clear=False):
        if clear:
            self.label.set_text('')
        else:
            self.label.set_text(row.full_data)

    def get_rows(self):
        rows = self.session.query(db.Book).all() 
        dicts = [r.__dict__ for r in rows]
        self.full_rows = ['id:' + str(d['book_id']) + '\t' + d['author_first_name'] + ' ' + d['author_last_name'] + ' ' + d['title'] + ' ' + str(d['year']) for d in dicts]
        self.printable_rows = [d['title'] + ' ' + str(d['year']) for d in dicts]
    
    def refresh_rows(self):
        self.get_rows() # pull data from db
        self.rows_box = Gtk.ListBox()
        self.add_rows()
        self.show_all()

    def choose_popup(self, widget,  open_db):
        if open_db:
            dialog = Gtk.FileChooserDialog(
                title="Select DB", parent=self, action=Gtk.FileChooserAction.OPEN
            )
        else:
            dialog = Gtk.FileChooserDialog(
                title="Select DB", parent=self, action=Gtk.FileChooserAction.SAVE
            )
        dialog.add_buttons(
            Gtk.STOCK_CANCEL,
            Gtk.ResponseType.CANCEL,
            Gtk.STOCK_OPEN,
            Gtk.ResponseType.OK,
        )

        response = dialog.run()
        if response == Gtk.ResponseType.OK:
            self.session = run_db(dialog.get_filename())
            self.update_row_desc(None, None, clear=True)
            if hasattr(self, 'rows_box'):
                self.rows_box.destroy()
            self.turn_action_btns(True)
            self.refresh_rows()
        elif response == Gtk.ResponseType.CANCEL:
            pass

        dialog.destroy()


    def create_popup(self, btn, columns, action):
        pop = Gtk.MessageDialog(
                     transient_for=self,
                     flags=0,
                     message_type=Gtk.MessageType.INFO,
                     buttons=Gtk.ButtonsType.OK,
                     text=action,
                     )
        pop.add_buttons(Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL)
        pop_box = pop.get_content_area()
        if action == 'Modify':
            up_label = Gtk.Label(label='Insert row to modify')
        elif action == 'Add':
            up_label = Gtk.Label(label='Insert row to add')
        elif action == 'Delete':
            up_label = Gtk.Label(label='Insert row to delete')
        pop_box.pack_start(up_label, True, True, 0)
        input_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=1)
        labels = {}
        entries = {}
        for col in columns:
            labels[col] = Gtk.Label(label=col)
            entries[col] = Gtk.Entry()
        for col in columns:
            input_box.pack_start(labels[col], True, True, 0)
            input_box.pack_start(entries[col], True, True, 0)
        pop_box.pack_start(input_box, True, True, 0)
        if action == 'Modify':
            new_val_label = Gtk.Label(label='New values')
            pop_box.pack_start(new_val_label, True, True, 0)
            new_val_input_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=1)
            for col in columns:
                col = 'new_' + col
                labels[col] = Gtk.Label(label=col)
                entries[col] = Gtk.Entry()
            for col in columns:
                col = 'new_' + col
                new_val_input_box.pack_start(labels[col], True, True, 0)
                new_val_input_box.pack_start(entries[col], True, True, 0)
            pop_box.pack_start(new_val_input_box, True, True, 0)

        # run popup window
        pop.show_all()
        response = pop.run()

        input_data = {}
        new_val_data = {}
        for col, entry in entries.items(): # get input to process
            if entries[col].get_text() != '':
                if action == 'Modify' and col[:4] == 'new_':
                    new_val_data[col[4:]] = entries[col].get_text()
                else:
                    input_data[col] = entry.get_text()

        # processing data from user input
        if response == Gtk.ResponseType.OK:
            self.update_row_desc(None, None, clear=True)
            self.rows_box.destroy()
            self.handle_req(action, input_data, new_val_data)
            self.refresh_rows()
            self.show_all()
        elif response == Gtk.ResponseType.CANCEL:
            pass
        pop.destroy()

    def handle_req(self, action, row, new_row):
        if action == 'Add':
            db.modify(delete=False, table='Book', **row)
        elif action == 'Delete':
            db.modify(delete=True, table='Book', **row)
        elif action == 'Modify':
            db.modify(delete=True, table='Book', **row)
            db.modify(delete=False, table='Book', **new_row)



def run_db(path):
    return db.init(path)


if __name__ == '__main__':
    session = db.init()
    app = App()
    app.show_all()
    Gtk.main()
    session.close()
