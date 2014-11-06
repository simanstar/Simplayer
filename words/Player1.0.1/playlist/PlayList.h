#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <QtWidgets>


class SearchBar;
class DefaultList;
class CurrentList;
class MediaFileItem;

class PlayList : public QWidget
{
     Q_OBJECT


public:
    explicit PlayList(QWidget *parent=0);
    ~PlayList();
    DefaultList *defaultlist;
    CurrentList *currentlist;
signals:
    void mediaChanged(QString filePath);


public slots:
        void addFile(QStringList *fileList);

private:
    QToolButton *currentbutton;
    QToolButton *defaultbutton;
    SearchBar   *searchbar;









private slots:
    void show_default_list();
    void show_current_list();
    void doubleSelectMedia(QListWidgetItem *item);
  //void read_file_form_open();



signals:
    void change_index(int);








};





class SearchBar : public QLineEdit
{

  //   Q_OBJECT
public:
    explicit SearchBar(QWidget *parent=0);
    ~SearchBar();
};




class DefaultList : public QListWidget
{

   Q_OBJECT
public:
    explicit DefaultList(QWidget *parent=0);
    ~DefaultList();
      void add_file(QStringList *fileList);
    QString getSelectedFile(MediaFileItem *item);
private:
   enum{ MagicNumber = 0x7F51C883};
   QMenu *popMenu;
   QAction *modify_action;
   QAction *delete_action;
   void contextMenuEvent ( QContextMenuEvent * event );
   void read_file();
   void return_media_item(int row);

private slots:
       void write_file();
        void search_text(QString text);
        void modify_item_text();
        void delete_item();
signals:
       void sequence_changed();
         void change_index(int);


};






class CurrentList : public QListWidget
{

     Q_OBJECT
public:
      explicit CurrentList(QWidget *parent=0);
      ~CurrentList();

      QString getSelectedFile(MediaFileItem *item);
private:
      enum{ MagicNumber = 0x7F51C883};
      QMenu *popMenu;
      QAction *modify_action;
      QAction *delete_action;

      void contextMenuEvent ( QContextMenuEvent * event );
      void read_file();
       void return_media_item(int row);
private slots:
    void to_top(QListWidgetItem* item);
    void write_file();
    void search_text(QString text);
    void modify_item_text();
    void delete_item();
signals:
     void sequence_changed();
       void change_index(int);
};



class MediaFileItem : public QListWidgetItem
{

  //   Q_OBJECT
  public:
    explicit MediaFileItem ();
    ~MediaFileItem ();

    QString filename_full;
    QString filename;



};
#endif // PLAYLIST_H
