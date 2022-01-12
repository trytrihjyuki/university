import argparse
import db_engine as db

def parse():
    parser = argparse.ArgumentParser(description='List the content of a folder')
    parser.add_argument('table', help='specify which table program is working on', type=str)
    parser.add_argument('-a', '--add', help='add record to database\nFriend(first, last, phone, email) or\nBook(author1, author2, title, year)', nargs='*')
    parser.add_argument('-d', '--delete', help='delete record from database\nFriend(first, last, phone, email) or\nBook(author1, author2, title, year)', nargs='*')
    parser.add_argument('-p ', '--print', help='print n rows of records from database', type=int)
    parser.add_argument('-l ', '--lend', help='lend a book to a friend (book_id, friend_id)', nargs=2)
    parser.add_argument('-o ', '--donate', help='return a book borrowed by friend (book_id, friend_id)', nargs=2)
    args = parser.parse_args()

    return args 

def handle(args):
    table = args.table
    if args.add:
        if table == 'Friend':
            db.modify(delete=False, table=table, first_name=args.add[0], last_name=args.add[1], phone=args.add[2], email=args.add[3])
        elif table == 'Book':
            db.modify(delete=False, table=table, author_first_name=args.add[0], author_last_name=args.add[1], title=args.add[2], year=args.add[3])
    elif args.delete:
        if table == 'Friend':
            db.modify(delete=True, table=table, first_name=args.delete[0], last_name=args.delete[1], phone=args.delete[2], email=args.delete[3])
        elif table == 'Book':
            db.modify(delete=True, table=table, author_first_name=args.delete[0], author_last_name=args.delete[1], title=args.delete[2], year=args.delete[3])
    elif args.print:
        db.print_rows(table, args.print)
    elif args.lend:
        db.lend(book_id=args.lend[0], friend_id=args.lend[1])
    elif args.donate:
        db.donate(book_id=args.donate[0], friend_id=args.donate[1])

if __name__ == '__main__':
    session = db.init()
    args = parse()
    handle(args)
    session.close()
