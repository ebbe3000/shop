#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QVector>


/// Class which stores information about prodcut
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

    /// Default constructor
    Product() = default;

    /// Constructor to initialize Product when product id is known and user id not
    ///
    /// @param id_p products' id
    /// @param name products' name
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path path to single image
    Product(const int id_p, const QString& name, const double price,
            const int amount, const QString& add_date,
            const QString& description, const QString& img_path);

    /// Constructor to initialize Product when product id is known and user id not
    ///
    /// @param id_p products' id
    /// @param name products' name
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path paths images
    Product(const int id_p, const QString& name, const double price,
            const int amount, const QString& add_date,
            const QString& description, const QVector<QString>& img_path);

    /// Constructor to initialize Product when product id is known and user id not
    ///
    /// @param id_p products' id
    /// @param name products' name
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path path to single image
    Product(const int id_p, QString&& name, const double price,
            const int amount, QString&& add_date,
            QString&& description, QString&& img_path);

    /// Constructor to initialize Product when product id is known and user id not
    ///
    /// @param id_p products' id
    /// @param name products' name
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path paths images
    Product(const int id_p, QString&& name, const double price,
            const int amount, QString&& add_date,
            QString&& description, QVector<QString>&& img_path);

    /// Constructor to initialize Product when product id and user is not known
    ///
    /// @param id_p products' id
    /// @param name products' name
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path path to single image
    Product(const QString& name, const double price,
            const int amount, const QString& add_date,
            const QString& description, const QString& img_path);

    /// Constructor to initialize Product when product id and user is not known
    ///
    /// @param id_p products' id
    /// @param name products' name
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path paths to images
    Product(const QString& name, const double price,
            const int amount, const QString& add_date,
            const QString& description, const QVector<QString>& img_path);

    /// Constructor to initialize Product when product id and user is not known
    ///
    /// @param id_p products' id
    /// @param name products' name
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path path to single image
    Product(QString&& name, const double price,
            const int amount, QString&& add_date,
            QString&& description, QString&& img_path);

    /// Constructor to initialize Product when product id and user is not known
    ///
    /// @param id_p products' id
    /// @param name products' name
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path paths to images
    Product(QString&& name, const double price,
            const int amount, QString&& add_date,
            QString&& description, QVector<QString>&& img_path);








    /// Constructor to initialize Product when product id and user is known
    ///
    /// @param id_p products' id
    /// @param id_u sellers' id
    /// @param name products' name
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path path to single image
    Product(const int id_p, const int id_u, const QString& name, const double price,
            const int amount, const QString& add_date,
            const QString& description, const QString& img_path);

    /// Constructor to initialize Product when product id and user id is known
    ///
    /// @param id_p products' id
    /// @param id_u sellers' id
    /// @param name products' name
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path paths to images
    Product(const int id_p, const int id_u, const QString& name, const double price,
            const int amount, const QString& add_date,
            const QString& description, const QVector<QString>& img_path);

    /// Constructor to initialize Product when product id and user id is known
    ///
    /// @param id_p products' id
    /// @param id_u sellers' id
    /// @param name products' name
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path path to single image
    Product(const int id_p, const int id_u, QString&& name, const double price,
            const int amount, QString&& add_date,
            QString&& description, QString&& img_path);

    /// Constructor to initialize Product when product id and user id is known
    ///
    /// @param id_p products' id
    /// @param id_u sellers' id
    /// @param name products' name
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path paths to images
    Product(const int id_p, const int id_u, QString&& name, const double price,
            const int amount, QString&& add_date,
            QString&& description, QVector<QString>&& img_path);

    /// Constructor to initialize Product when user id is known and product id is not
    ///
    /// @param name products' name
    /// @param id_u sellers' id
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path path to single image
    Product(const QString& name, const int id_u, const double price,
            const int amount, const QString& add_date,
            const QString& description, const QString& img_path);

    /// Constructor to initialize Product when user id is known and product id is not
    ///
    /// @param name products' name
    /// @param id_u sellers' id
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path paths images
    Product(const QString& name, const int id_u, const double price,
            const int amount, const QString& add_date,
            const QString& description, const QVector<QString>& img_path);

    /// Constructor to initialize Product when user id is known and product id is not
    ///
    /// @param name products' name
    /// @param id_u sellers' id
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path path to single image
    Product(QString&& name, const int id_u, const double price,
            const int amount, QString&& add_date,
            QString&& description, QString&& img_path);

    /// Constructor to initialize Product when user id is known and product id is not
    ///
    /// @param name products' name
    /// @param id_u sellers' id
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path paths images
    Product(QString&& name, const int id_u, const double price,
            const int amount, QString&& add_date,
            QString&& description, QVector<QString>&& img_path);

    /// Constructor to initialize Product when user id, add_date and img_paths are not known
    ///
    /// @param name products' name
    /// @param id_u sellers' id
    /// @param price products' price
    /// @param amount copies number
    /// @param add_date products' add date
    /// @param description products' description
    /// @param img_path path to single image
    Product(QString&& name, const int id_u, const double price,
            const int amount, QString&& description);


    /// Method return products' id
    ///
    /// @return int products' id
    int getId() const;

    /// Method return sellers' id
    ///
    /// @return int sellers' id
    int getIdU() const;

    /// Method return products' name
    ///
    /// @return QString products' name
    QString getName() const;

    /// Method return products' price
    ///
    /// @return double products' price
    double getPrice() const;

    /// Method return products amount
    ///
    /// @return int products amount
    int getAmount() const;

    /// Method return products add date
    ///
    /// @return QString products' add date
    QString getAddDate() const;

    /// Method return products description
    ///
    /// @return QString products' description
    QString getDescription() const;

    /// Method return products paths
    ///
    /// @return QVector<QString> products' paths
    QVector<QString> getImgPath() const;


    /// Method to set productsid
    ///
    /// @param id products' id
    /// @return void
    void setId(int id);

    /// Method to set products name
    ///
    /// @param name products' name
    /// @return void
    void setName(const QString& name);

    /// Method to set products name
    ///
    /// @param name products' name
    /// @return void
    void setName(QString&& name);

    /// Method to set products' price
    ///
    /// @param price products' price
    /// @return void
    void setPrice(double price);

    /// Method to set products' amount
    ///
    /// @param amount products' amount
    /// @return void
    void setAmount(int amount);

    /// Method to set products' add date
    ///
    /// @param add_date products' add date
    /// @return void
    void setAddDate(const QString& add_date);

    /// Method to set products' add date
    ///
    /// @param add_date products' add date
    /// @return void
    void setAddDate(QString&& add_date);

    /// Method to set products' description
    ///
    /// @param description products' description
    /// @return void
    void setDescription(const QString& description);

    /// Method to set products' description
    ///
    /// @param description products' description
    /// @return void
    void setDescription(QString&& description);

    /// Method to set products' img path
    ///
    /// @param img_path products' img path
    /// @return void
    void setImgPath(const QString& img_path);

    /// Method to set products' imgs paths
    ///
    /// @param img_path products' imgs paths
    /// @return void
    void setImgPath(const QVector<QString>& img_path);

    /// Method to set products' img path
    ///
    /// @param img_path products' img path
    /// @return void
    void setImgPath(QString&& img_path);

    /// Method to set products' imgs paths
    ///
    /// @param img_path products' imgs paths
    /// @return void
    void setImgPath(QVector<QString>&& img_path);
};

#endif // PRODUCT_H
