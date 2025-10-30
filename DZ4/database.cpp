#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

    dataBase = new QSqlDatabase();
tableWidget = new QTableWidget();

}

DataBase::~DataBase()
{
    delete dataBase;
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(QString driver, QString nameDB)
{

    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);

}

/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(QVector<QString> data)
{


    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());




    bool status;
    status = dataBase->open( );
    if (!dataBase->open()) {
        qDebug() << "Error:" << dataBase->lastError().text();
    } else {
        qDebug() << "Succes!";
        QSqlQuery q(*dataBase);
        q.exec("SELECT table_name FROM information_schema.tables WHERE table_schema = 'public';");
        while (q.next())
            qDebug() << "Таблица:" << q.value(0).toString();
    }

    emit sig_SendStatusConnection(status);
model = new QSqlTableModel(this, *dataBase);
    query = new QSqlQueryModel( );
}
/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{

    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();

}
/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */
    void DataBase::RequestToDB( int requestType)
    {

        model->setTable("film");
        model->select();

        QString genre = (requestType == requestComedy) ? "Comedy" : "Horror";


        query->setQuery(
            "SELECT f.title, f.description "
            "FROM film f "
            "JOIN film_category fc ON f.film_id = fc.film_id "
            "JOIN category c ON c.category_id = fc.category_id "
            "WHERE c.name = '" + genre + "'",
            *dataBase
            );

emit sig_SendStatusRequest(query->lastError( ));
    }

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}

void DataBase::ReadAnswerFromDB(int requestType)
{
    /*
     * Используем оператор switch для разделения запросов
    */

    switch (requestType) {
    //Для наших запросов вид таблицы не поменяетя. Поэтому бужет единый обработчик.
    case requestAllFilms:
    {
        QStringList headers;

        int titleCol = model->fieldIndex("title");
        int descCol = model->fieldIndex("description");
        tableWidget->setRowCount(model->rowCount());
        tableWidget->setColumnCount(2);
        headers << "Название" << "Описание";
        tableWidget->setHorizontalHeaderLabels(headers);
        for (int i = 0; i < model->rowCount(); ++i) {
            QString title = model->data(model->index(i, titleCol)).toString();
            QString desc = model->data(model->index(i, descCol)).toString();


            tableWidget->setItem(i, 0, new QTableWidgetItem(title));
            tableWidget->setItem(i, 1, new QTableWidgetItem(desc));
        }

        emit sig_SendDataFromDB(tableWidget, requestType);

    }
        break;
    case requestComedy:
    case requestHorrors:
    {
        QStringList headers;

        headers << "Название" << "Описание";
        tableWidget->setHorizontalHeaderLabels(headers);
        tableWidget->setColumnCount(2);
        for(int i = 0; i < query->rowCount(); ++i){
            tableWidget->insertRow(i);
            tableWidget->setItem(i, 0, new QTableWidgetItem(query->data(query->index(i, 0)).toString()));
            tableWidget->setItem(i, 1, new QTableWidgetItem(query->data(query->index(i, 1)).toString()));
        }
emit sig_SendDataFromDB(tableWidget, requestType);
        int x= 0;
    }


        break;


    default:
        break;
    }
}
