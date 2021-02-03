#include "book.h"

QString Book::getBookName() const
{
    return bookName;
}

void Book::setBookName(const QString &value)
{
    bookName = value;
}

QString Book::getBookAuthor() const
{
    return bookAuthor;
}

void Book::setBookAuthor(const QString &value)
{
    bookAuthor = value;
}

Book::Book()
{

}
