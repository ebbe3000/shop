#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QVector>

class Product
{
    int id_p_;
    QString name_;
    int id_u_;
    double price_;
    int amount_;
    QString add_date_;
    QString description_;
    QVector<QString> img_path_;


public:
    Product() = default;

    Product(const int id_p, const QString& name, const double price,
            const int amount, const QString& add_date,
            const QString& description, const QString& img_path);


    Product(const int id_p, const QString& name, const double price,
            const int amount, const QString& add_date,
            const QString& description, const QVector<QString>& img_path);


    Product(const int id_p, QString&& name, const double price,
            const int amount, QString&& add_date,
            QString&& description, QString&& img_path);


    Product(const int id_p, QString&& name, const double price,
            const int amount, QString&& add_date,
            QString&& description, QVector<QString>&& img_path);


    Product(const QString& name, const double price,
            const int amount, const QString& add_date,
            const QString& description, const QString& img_path);


    Product(const QString& name, const double price,
            const int amount, const QString& add_date,
            const QString& description, const QVector<QString>& img_path);


    Product(QString&& name, const double price,
            const int amount, QString&& add_date,
            QString&& description, QString&& img_path);


    Product(QString&& name, const double price,
            const int amount, QString&& add_date,
            QString&& description, QVector<QString>&& img_path);









    Product(const int id_p, const int id_u, const QString& name, const double price,
            const int amount, const QString& add_date,
            const QString& description, const QString& img_path);


    Product(const int id_p, const int id_u, const QString& name, const double price,
            const int amount, const QString& add_date,
            const QString& description, const QVector<QString>& img_path);


    Product(const int id_p, const int id_u, QString&& name, const double price,
            const int amount, QString&& add_date,
            QString&& description, QString&& img_path);


    Product(const int id_p, const int id_u, QString&& name, const double price,
            const int amount, QString&& add_date,
            QString&& description, QVector<QString>&& img_path);


    Product(const QString& name, const int id_u, const double price,
            const int amount, const QString& add_date,
            const QString& description, const QString& img_path);


    Product(const QString& name, const int id_u, const double price,
            const int amount, const QString& add_date,
            const QString& description, const QVector<QString>& img_path);


    Product(QString&& name, const int id_u, const double price,
            const int amount, QString&& add_date,
            QString&& description, QString&& img_path);


    Product(QString&& name, const int id_u, const double price,
            const int amount, QString&& add_date,
            QString&& description, QVector<QString>&& img_path);


    Product(QString&& name, const int id_u, const double price,
            const int amount, QString&& description);


    int getId() const;
    int getIdU() const;
    QString getName() const;
    double getPrice() const;
    int getAmount() const;
    QString getAddDate() const;
    QString getDescribtion() const;
    QVector<QString> getImgPath() const;


    void setId(int id);
    void setName(const QString& name);
    void setName(QString&& name);
    void setPrice(double price);
    void setAmount(int amount);
    void setAddDate(const QString& add_date);
    void setAddDate(QString&& add_date);
    void setDescription(const QString& describtion);
    void setDescription(QString&& describtion);
    void setImgPath(const QString& img_path);
    void setImgPath(const QVector<QString>& img_path);
    void setImgPath(QString&& img_path);
    void setImgPath(QVector<QString>&& img_path);
};

#endif // PRODUCT_H
