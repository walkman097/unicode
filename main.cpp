#include <QString>
#include <QTextCodec>
#include <QDebug>


static std::string getGbkString(const std::string &str) {
	std::string ret;
	static const int charSize = 2;

	static const char xcode = '%';
	for (size_t i=0; i<str.length(); ) {
		if (str[i] == xcode) {
			i += 1;
			QString s(str.substr(i, charSize).c_str());
			ret += s.toInt(NULL, 16) & 0xff;
			i += charSize;
		} else {
			ret += str[i];
			i++;
		}
	}

	return ret;
}


int main()
{
	const char *src = "708%C4%A9%C8%D5%CA%B9%D5%DF%C2%B7%CE%F7%B7%A8lsdkkhdfka094";
	//const char *src = "%B4%D30%B5%BD1%A3%BA%BF%AA%C6%F4%C9%CC%D2%B5%D3%EB%CE%B4%C0%B4%B5%C4%C3%D8%C3%DC(%B5%E7%D7%D3%CA%E9)%A3%AD%A3%AD40%D5%DB%A3%AC%B5%B1%B5%B1%BC%DB%A3%BA%A3%A418.00";
	std::string gbkStr = getGbkString(src);
	QTextCodec *codec = QTextCodec::codecForName("GBK");
	qDebug() << codec->toUnicode(gbkStr.c_str());
}
