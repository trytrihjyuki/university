import datetime
from sqlalchemy.orm import relationship, backref
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Table, Column, Integer, ForeignKey, String, DateTime
from sqlalchemy import and_ 
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

Base = declarative_base()


class Friend(Base):
    __tablename__ = "Friend"
    friend_id = Column(Integer, primary_key=True)
    first_name = Column(String, nullable=False)
    last_name = Column(String, nullable=False)
    phone = Column(String) 
    email = Column(String)

    borrowings = relationship("Borrowing")

class Book(Base):
    __tablename__ = "Book"
    book_id = Column(Integer, primary_key=True)
    author_first_name = Column(String)
    author_last_name = Column(String)
    title = Column(String)
    year = Column(Integer)
    borrowings = relationship("Borrowing") 

class Borrowing(Base):
    __tablename__ = "Borrowing"
    borrowing_id = Column(Integer, primary_key=True)
    friend_id = Column(Integer, ForeignKey("Friend.friend_id"))
    book_id = Column(Integer, ForeignKey("Book.book_id"))
    data = Column(DateTime, default=datetime.datetime.utcnow)

def init():
    engine = create_engine('sqlite:////tmp/temp.db', echo=False)
    Session = sessionmaker(bind=engine)
    Base.metadata.create_all(engine)
    global session
    session = Session()
    return session


def modify(delete, **kwargs):
    global session
    if kwargs['table'] == 'Book':
        book = (
            session.query(Book).filter(
                and_(
                    Book.title == kwargs['title'], Book.author_first_name == kwargs['author_first_name'], Book.author_last_name == kwargs['author_last_name'], Book.year == kwargs['year']
                )
            )
            .one_or_none()
        )
        if delete:
            session.query(Book).filter(Book.book_id==book.book_id).delete()
        else:
            if book is not None: # book exist in database
                return
            book = Book(author_first_name=kwargs['author_first_name'], author_last_name=kwargs['author_last_name'], title=kwargs['title'], year=kwargs['year'])
            session.add(book)
    elif kwargs['table'] == 'Friend':
        friend = (
            session.query(Friend).filter(
                and_(
                    Friend.first_name == kwargs['first_name'], Friend.last_name == kwargs['last_name'], Friend.email == kwargs['email'], Friend.phone == kwargs['phone']
                )
            )
            .one_or_none()
        )
        if delete:
            session.query(Friend).filter(Friend.friend_id==friend.friend_id).delete()
        else:
            if friend is not None: # friend exist in database
                return
            friend = Friend(first_name=kwargs['first_name'], last_name=kwargs['last_name'], phone=kwargs['phone'], email=kwargs['email'])
            session.add(friend)
    elif kwargs['table'] == 'Borrowing':
        # here we have guarantee that book_id and friend_id are valid values
        if delete:
            session.query(Borrowing).filter(Borrowing.borrowing_id==kwargs['borrowing_id']).delete()
        else:
            borrowing = Borrowing(friend_id=kwargs['friend_id'], book_id=kwargs['book_id'])
            session.add(borrowing)
    else:
        raise ValueError('Doesn\'t recognize table name!')

    session.commit()

def print_rows(table, n):
    global session
    if table == 'Friend':
        rows = session.query(Friend).limit(n).all() 
    elif table == 'Book':
        rows = session.query(Book).limit(n).all() 
    elif table == 'Borrowing':
        rows = session.query(Borrowing).limit(n).all()
    
    for r in rows:
        print(list(r.__dict__.values())[1:])

# functions to lend and return books
def lend(book_id, friend_id):
    global session
    b = session.query(Borrowing).filter(Borrowing.book_id == book_id).one_or_none()
    if b is not None:
        raise ValueError('Book is already borrowed!')
    b = session.query(Book).filter(Book.book_id == book_id).one_or_none()
    if b is None:
        raise ValueError('Book doesn\'t exist!')
    f = session.query(Friend).filter(Friend.friend_id == friend_id).one_or_none()
    if f is None:
        raise ValueError('Friend doesn\'t exist!')
    
    modify(delete=False, table='Borrowing', friend_id=friend_id, book_id=book_id)

def donate(book_id, friend_id):
    global session
    br = session.query(Borrowing).filter(Borrowing.book_id == book_id, Borrowing.friend_id == friend_id).one_or_none()
    if br is None:
        raise ValueError('Book is not borrowed by this friend!')
    b = session.query(Book).filter(Book.book_id == book_id).one_or_none()
    if b is None:
        raise ValueError('Book doesn\'t exist!')
    f = session.query(Friend).filter(Friend.friend_id == friend_id).one_or_none()
    if f is None:
        raise ValueError('Friend doesn\'t exist!')

    modify(delete=True, table='Borrowing', borrowing_id=br.borrowing_id)
