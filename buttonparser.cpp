#include "buttonparser.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include "actionbuttondata.h"

ButtonParser::ButtonParser() {

}

const std::vector<const ActionButtonData*> ButtonParser::parse() {

    std::vector<const ActionButtonData*> vector;

    QFile file("napit.conf");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(nullptr, "Lukuvirhe", "napit.conf-tiedostoa ei ollut olemassa.");
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");
        ActionButtonData* data = new ActionButtonData(fields);
        vector.push_back(data);
    }

    file.close();

    return vector;
}
