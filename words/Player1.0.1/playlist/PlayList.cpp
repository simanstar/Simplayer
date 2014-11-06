#include "PlayList.h"

//    QWidget(parent)
PlayList::PlayList(QWidget *parent)
{
    QToolButton *currentbutton=new QToolButton(this);
    QToolButton *defaultbutton=new QToolButton(this);
    SearchBar   *searchbar=new SearchBar(this);
    defaultlist=new DefaultList(this);
    currentlist=new CurrentList(this);

    defaultbutton->setText("默认列表");
   currentbutton->setText("最近列表");
//    MediaFileItem *item1=new MediaFileItem;
//    item1->setText("太年轻.mp4");
//    item1->filename_full="太年轻.mp4";
//    item1->filename="太年轻.mp4";


//    MediaFileItem *item2=new MediaFileItem;
//    item2->setText("一生所爱.mkv");
//    item2->filename_full="一生所爱.mkv";
//    item2->filename="一生所爱.mkv";

  // defaultlist->addItem(item1);
  // currentlist->addItem(item2);



/////以下开始布局
    //按扭水平布局
    QHBoxLayout *button_layout=new QHBoxLayout;
      button_layout->addWidget(defaultbutton);
    button_layout->addWidget(currentbutton);


    //列表重叠布局
    QStackedLayout *list_layout=new QStackedLayout;
    list_layout->addWidget(defaultlist);
    list_layout->addWidget(currentlist);

    //总的垂直布局

    QVBoxLayout  *overall_layout=new QVBoxLayout;
    overall_layout->addLayout(button_layout);
    overall_layout->addWidget(searchbar);
    overall_layout->addLayout(list_layout);

    //把总布局添加到listwidget


    this->setLayout(overall_layout);
///////////////////////////////////////////////////////////////布局完毕,开始connect
    //切换list
    connect(currentbutton,SIGNAL(clicked()),this,SLOT(show_current_list()));
    connect(defaultbutton,SIGNAL(clicked()),this,SLOT(show_default_list()));
   connect(this,SIGNAL(change_index(int)),list_layout,SLOT(setCurrentIndex(int)));
   connect(defaultlist,SIGNAL(change_index(int)),list_layout,SLOT(setCurrentIndex(int)));
   connect(currentlist,SIGNAL(change_index(int)),list_layout,SLOT(setCurrentIndex(int)));
   //done

   //双击某项后，把该项置顶
   connect(defaultlist,SIGNAL(itemDoubleClicked(QListWidgetItem*)),currentlist,SLOT(to_top(QListWidgetItem*)));
   connect (currentlist,SIGNAL(itemDoubleClicked(QListWidgetItem*)),currentlist,SLOT(to_top(QListWidgetItem*)));
    //双击某项后，播放该项
   connect(defaultlist,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(doubleSelectMedia(QListWidgetItem*)));
   connect (currentlist,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(doubleSelectMedia(QListWidgetItem*)));
   //done

   //写入文件
   connect(defaultlist,SIGNAL(sequence_changed()),defaultlist,SLOT(write_file()));
    connect(currentlist,SIGNAL(sequence_changed()),currentlist,SLOT(write_file()));


   //搜索框

    connect(searchbar,SIGNAL(textChanged(QString)),defaultlist,SLOT(search_text(QString)));
    connect(searchbar,SIGNAL(textChanged(QString)),currentlist,SLOT(search_text(QString)));


////////////////////////////////////////////////////////////////connect完毕
    ////样式

        this->setStyleSheet(" QToolButton{ border: 2px solid #F5F5F6;border-radius:10px;padding:4px;background-color:rgb(123,124,122,0);font:bold 12px;}"
                                     "QToolButton:hover{background-color:rgb(123,124,122,80);}");


}


PlayList::~PlayList()
{

}

void PlayList::addFile(QStringList *fileList)
{
    defaultlist->add_file(fileList);
}

void PlayList::show_current_list()
{
    emit change_index(1);
}

void PlayList::show_default_list()
{

 emit change_index(0);

}
void PlayList::doubleSelectMedia(QListWidgetItem *item)
{
    if(sender()==this->defaultlist)
    {
        emit mediaChanged(defaultlist->getSelectedFile((MediaFileItem*)item));
    }
    else if(sender()==this->currentlist)
    {
        emit mediaChanged(currentlist->getSelectedFile((MediaFileItem*)item));
    }
}

///////////////////////////////////////////////////////搜索框
SearchBar::SearchBar(QWidget *parent)
{
    this->setStyleSheet("  border: 2px solid #F5F5F6;border-radius:10px;padding:4px;background-color:rgb(123,124,122,0)");
}

SearchBar::~SearchBar()
{

}


////////////////////////////////////////////////////////默认列表
DefaultList::DefaultList(QWidget *parent)
{

    popMenu =new QMenu(this);
    modify_action=new QAction("修改",this);
    delete_action=new QAction("删除",this);

    popMenu->addAction(modify_action);
    popMenu->addAction(delete_action);

    connect(this->delete_action,SIGNAL(triggered()),this,SLOT(delete_item()));


    //首先读取文件，初始化
     read_file();

     this->setStyleSheet(" QListWidget{ border: 2px solid #F5F5F6;border-radius:10px;padding:4px;background-color:rgb(123,124,122,0)}");
}

 DefaultList::~DefaultList()
{

}



 void DefaultList::add_file(QStringList *fileList)
 {
     MediaFileItem *itemTemp;
     QFileInfo fileInfo;
     for(int i=0;i<fileList->size();i++)
     {

         fileInfo=QFileInfo(fileList->at(i));
         itemTemp=new MediaFileItem;
         itemTemp->filename_full=fileList->at(i);
         itemTemp->filename=fileInfo.fileName();
         itemTemp->setText(fileInfo.fileName());


         this->insertItem(0,itemTemp);



     }



     emit sequence_changed();
 }
QString DefaultList::getSelectedFile(MediaFileItem *item)
{
    return item->filename_full;
}


void DefaultList::read_file()
{
      QFile file("defaultlist.txt");
      if (!file.open(QIODevice::ReadOnly)) {
//          QMessageBox::warning(this, tr("SimPlayer"),
//                               tr("Cannot read file %1:\n%2.")
//                               .arg(file.fileName())
//                               .arg(file.errorString()));
          return;
      }

       QDataStream in(&file);
       in.setVersion(QDataStream::Qt_5_1);


       quint32 magic;
       in >> magic;
       if (magic != MagicNumber) {
//           QMessageBox::warning(this, tr("SimPlayer"),
//                                tr("The file is not a list file."));
         return ;
       }

        clear();



        quint16 row;

        QString str1,str2;
        MediaFileItem * temp;
        QApplication::setOverrideCursor(Qt::WaitCursor);
        while (!in.atEnd()) {
            in >> row >> str1>>str2;
            temp=new MediaFileItem;
            temp->filename_full=str1;
            temp->filename=str2;
            temp->setText(str2);
            this->addItem(temp);
          this->insertItem(row, temp);

        }
        QApplication::restoreOverrideCursor();
      //  return true;

         //done




}
 void DefaultList::write_file()
 {

           QFile file2("defaultlist.txt");
              if (!file2.open(QIODevice::WriteOnly)) {
//                  QMessageBox::warning(this, tr("SimPlayer"),
//                                       tr("Cannot write file %1:\n%2.")
//                                       .arg(file2.fileName())
//                                       .arg(file2.errorString()));
                  return ;
              }

              QDataStream out(&file2);
              out.setVersion(QDataStream::Qt_5_1);

              out << quint32(MagicNumber);

              QApplication::setOverrideCursor(Qt::WaitCursor);
              MediaFileItem *item_temp;

              for ( int row=0; row <this->count(); ++row) {

                  item_temp=(MediaFileItem*)this->item(row);
                      QString str1 =item_temp->filename_full;
                      QString str2 =item_temp->filename;


                      if (!str1.isEmpty() && !str2.isEmpty())
                          out << quint16(row) << str1<<str2;

              }

              QApplication::restoreOverrideCursor();

 }



 void DefaultList::search_text(QString text)
 {
     int flag=0;
     for(int row=0;row <this->count();++row)
     {
         if(this->item(row)->text().indexOf(text)>=0)
         {
               this->item(row)->setSelected(1);
             flag=1;
         }
         else
         {
               this->item(row)->setSelected(0);
           //  flag=0;
         }

     }
     if(flag)
       emit change_index(0);
 }


void DefaultList::contextMenuEvent ( QContextMenuEvent * event )
{


    if(this->itemAt(mapFromGlobal(QCursor::pos())) != NULL) //判断右键的是否在item上面
      {



           popMenu->exec(QCursor::pos());


      }

}



void DefaultList::modify_item_text()
{

}


void DefaultList::delete_item()
{
    delete this->currentItem();

    emit sequence_changed();
}
////////////////////////////////////////////////////////最近列表
CurrentList::CurrentList(QWidget *parent)
{

    popMenu =new QMenu(this);
    modify_action=new QAction("修改",this);
    delete_action=new QAction("删除",this);

    popMenu->addAction(modify_action);
    popMenu->addAction(delete_action);
    connect(this->delete_action,SIGNAL(triggered()),this,SLOT(delete_item()));


   //首先读取文件，初始化

    read_file();

    this->setStyleSheet(" QListWidget{ border: 2px solid #F5F5F6;border-radius:10px;padding:4px;background-color:rgb(123,124,122,0)}");
}




 CurrentList::~CurrentList()
{

}



 QString CurrentList::getSelectedFile(MediaFileItem *item)
 {

       return item->filename_full;
 }


 //从文件currentlist里读出视频文件,并添加到列表中
void CurrentList::read_file()
{


      QFile file("currentlist.txt");
      if (!file.open(QIODevice::ReadOnly)) {
//          QMessageBox::warning(this, tr("SimPlayer"),
//                               tr("Cannot read file %1:\n%2.")
//                               .arg(file.fileName())
//                               .arg(file.errorString()));
        return ;
      }

       QDataStream in(&file);
       in.setVersion(QDataStream::Qt_5_1);


       quint32 magic;
       in >> magic;
       if (magic != MagicNumber) {
//           QMessageBox::warning(this, tr("SimPlayer"),
//                                tr("The file is not a list file."));
        return ;
       }

        clear();



        quint16 row;

        QString str1,str2;

        MediaFileItem * temp;
        QApplication::setOverrideCursor(Qt::WaitCursor);
        while (!in.atEnd()) {
            in >> row >> str1>>str2;

            temp=new MediaFileItem;
            temp->filename_full=str1;
            temp->filename=str2;

            temp->setText(str2);
           this->insertItem(row, temp);

        }
        QApplication::restoreOverrideCursor();
  //    return true;
    //done
}


//
 void CurrentList::write_file()
 {

           QFile file("currentlist.txt");
              if (!file.open(QIODevice::WriteOnly)) {
//                  QMessageBox::warning(this, tr("SimPlayer"),
//                                       tr("Cannot write file %1:\n%2.")
//                                       .arg(file.fileName())
//                                       .arg(file.errorString()));
                  return ;
              }

              QDataStream out(&file);
              out.setVersion(QDataStream::Qt_5_1);

              out << quint32(MagicNumber);

              QApplication::setOverrideCursor(Qt::WaitCursor);

               MediaFileItem *item_temp;

              for ( int row=0; row <this->count(); ++row) {

                  item_temp=(MediaFileItem*)this->item(row);
                      QString str1 =item_temp->filename_full;
                      QString str2 =item_temp->filename;


                      if (!str1.isEmpty() && !str2.isEmpty())
                          out << quint16(row) << str1<<str2;

              }

              QApplication::restoreOverrideCursor();

 }
void CurrentList::to_top(QListWidgetItem *item)
{
    int i;
    MediaFileItem *item_temp=(MediaFileItem*) item;
    for(i=0;i<this->count();i++)
    {
        if(this->item(i)->text()==item->text())
            break;
    }

    if(this->count()==i)  //一个都不相等
       {
         MediaFileItem *item_new=new MediaFileItem;

          *item_new=*item_temp;
         this->insertItem(0,item_new);

       }
    else
       {
          this->insertItem(0,this->takeItem(i));
          this->setCurrentRow(0);
       }

    emit sequence_changed();


}





void CurrentList::search_text(QString text)
{
    int flag=0;
    for(int row=0;row <this->count();++row)
    {
        if(this->item(row)->text().indexOf(text)>=0)
        {
              this->item(row)->setSelected(1);
            flag=1;
        }
        else

              {
                this->item(row)->setSelected(0);
              //  flag=0;
              }

    }
    if(flag)
      emit change_index(1);
}



void CurrentList::contextMenuEvent ( QContextMenuEvent * event )
{


    if(this->itemAt(mapFromGlobal(QCursor::pos())) != NULL) //判断右键的是否在item上面
      {



           popMenu->exec(QCursor::pos());


      }

}


void CurrentList::modify_item_text()
{

}


void CurrentList::delete_item()
{
    delete this->currentItem();

    emit sequence_changed();
}

////////////////////////////////////////////////////////媒体文件类
MediaFileItem ::MediaFileItem ()
{

}


MediaFileItem ::~MediaFileItem ()
{

}
