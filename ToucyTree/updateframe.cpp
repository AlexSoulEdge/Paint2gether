#include "mainwindow.h"

#include <QDebug>

void MainWindow::updateFrame(){
    if(client.poll()){
        char *received = new char [DEFAULT_BUFFER];
        int bytes_received = client.receiveData(received);
        SREQUEST fantastic_four = *reinterpret_cast <SREQUEST * > (received);
        std::string string_received(received + 4, bytes_received - 5);
        int syze = string_received.size();
        qDebug()<<syze;
        std::vector <std::string> strings;
        std::istringstream s_stream(string_received);
        qDebug()<< static_cast <uint32_t> (fantastic_four);
        switch(fantastic_four){
               case(SREQUEST::E_HELLO) : {
                    std::string s;
                    qDebug()<<s_stream.str().size();
                    while(std::getline(s_stream, s, '\0')){
                        QString str(s.c_str());
                        qDebug()<<str;
                        strings.push_back(s);
                    }
                    break;
               }
               default: break;
        }

        bool has_child = false;
        for(const auto &it : strings){
            const QString insert_in_tree(it);
            client.filename = insert_in_tree;
            if(has_child == true){
                client.insertRow(/*insert_in_tree*/);
           }
           else{
               client.insertChild(/*insert_in_tree*/);
               has_child = true;
           }
        }

        delete received;

    }
}
