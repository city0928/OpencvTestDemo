#include "widget.h"
#include "TestblobAnalyzer.h"

#include "opencv2/imgproc.hpp"
#include "BlobInfoList.h"
#include "ExecHelper.h"
//#include "LibImgProc/BlobAnalyzerCA.h"
//#include "LibImgProc/BlobAnalyzerCC.h"

#include <QApplication>
#include "opencv2/imgcodecs.hpp"
#include "Logger.h"

#define painterpainterpath 0
#define blobAnalyzer 0
#define sqlite3templateclass 1

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LinkSenseAIFI::LogParam libParam{ LinkSenseAIFI::LogMode::Both, "./Log", "LinkSenseIVS", "Running", ".log", 23, 59, 14 };
    libParam.level = LinkSenseAIFI::LogLevel::debug;
    LinkSenseAIFI::Logger& logger = LinkSenseAIFI::Logur::create(libParam);

#if painterpainterpath
    Widget w;
    w.resize(300, 600);
    w.show();
#elif blobAnalyzer
    TestblobAnalyzer obj;
    cv::Mat matTop = cv::imread("D:/guanzhaohang/desktop/T_PieceLayout.png", cv::IMREAD_GRAYSCALE);
    cv::Mat matBot = cv::imread("D:/guanzhaohang/desktop/B_PieceLayout.png", cv::IMREAD_GRAYSCALE);
    obj.findBlobAnalyzerCA(matTop);
    obj.show();
#elif sqlite3templateclass

#endif
    return a.exec();
}
