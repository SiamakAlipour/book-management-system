#ifndef BOOK_H
#define BOOK_H

#include <QWidget>
class Book
{
private:
    QString bookName;
    QString bookAuthor;
public:
    Book();

    QString getBookName() const;
    void setBookName(const QString &value);

    QString getBookAuthor() const;
    void setBookAuthor(const QString &value);
};

#endif // BOOK_H
