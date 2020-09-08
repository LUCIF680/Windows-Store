#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H
#pragma once
#include <util.hpp>
#include <QtMultimediaWidgets/QtMultimediaWidgets>
#include <future>
namespace Ui {
class VideoPlayer;
}
namespace ouroboros {
    class VideoPlayer : public Util{
        Q_OBJECT
        QMediaPlayer *media_player;
        QVideoWidget* video_player;
    public:
        explicit VideoPlayer(QWidget* parent = nullptr) : Util(parent){
            video_player = new QVideoWidget;
            const QRect availableGeometry = QApplication::desktop()->availableGeometry(video_player);
            video_player->resize(availableGeometry.width(), availableGeometry.height());
            video_player->setWindowFlags(Qt::CustomizeWindowHint);
            video_player->setStyleSheet("background-color:rgb(66,64,61)");
            video_player->show();
        }
        ~VideoPlayer() override{
            delete media_player;
            delete video_player;
        }
        void playVideo (){
            media_player = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
            media_player->setVideoOutput(video_player);
            media_player->setMedia(QUrl(url));
            media_player->play();
            connect(media_player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
                    this, &VideoPlayer::handleError); // Error dialog will open
        }
        void wait() override{
            QEventLoop loop;
            connect(this,SIGNAL(errorOccuerred()),&loop,SLOT(quit()));
            loop.exec();
        }
        bool refund(){
            qDebug() << 1;
            return true;
        }
    signals:
        void errorOccuerred();
    private slots:
        void closeErrorDialog() override{ error_dialog->close();     }
        void handleError(){
            std::future<bool> refund_complete = std::async(&VideoPlayer::refund,this);
            video_player->close();
            Util::setErrorBox(104);
            refund_complete.get();
            emit errorOccuerred();
        }
    };
}
#endif // VIDEOPLAYER_H
