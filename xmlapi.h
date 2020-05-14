#ifndef XMLAPI_H
#define XMLAPI_H

#include <QObject>
#include <QtXml>
#include <SOAP/qtsoap.h>

class xmlAPI : public QObject
{
    Q_OBJECT
public:
    xmlAPI()
    {

        connect(&http, SIGNAL(responseReady()), SLOT(getResponse()));
//doRequest();
    }
    QtSoapHttpTransport http;
public slots:
    void doRequest()
    {



    QtSoapMessage request;
    request.setMethod(QtSoapQName("DoStreamRequest", "http://tempuri.org/"));
   // request.
    request.addMethodArgument("msg", "", "msg");


    http.submitRequest(request, "/search/beta2");

qDebug() << request.toXmlString();
//        POST /LocalTcService.svc HTTP/1.1\r\n
//        Content-Type: text/xml; charset=utf-8\r\n
//        SOAPAction: "http://tempuri.org/ILocalTcService/DoStreamRequest"\r\n
//        Host: 10.1.7.11:27000\r\n
//        Accept-Encoding: gzip, deflate\r\n
//        \r\n
//        [Full request URI: http://10.1.7.11:27000/LocalTcService.svc]
//        <s:Envelope
//            xmlns:s="http://schemas.xmlsoap.org/soap/envelope/">
//            <s:Body>
//                <DoStreamRequest
//                    xmlns="http://tempuri.org/">
//                    <msg>
//                         [truncated]PABUAEMATQBlAHMAcwBhAGcAZQAgAHgAbQBsAG4AcwA9ACIAaAB0AHQAcAA6AC8ALwBzAGMAaABlAG0AYQBzAC4AZABhAHQAYQBjAG8AbgB0AHIAYQBjAHQALgBvAHIAZwAvADIAMAAwADQALwAwADcALwBUAEMALgBNAGUAcwBzAGEAZwBlACIAIAB4AG0AbABuAHMAOgBpAD0AIgBoAHQAdABwADoALw
//                        </msg>
//                    </DoStreamRequest>
//                </s:Body>
//            </s:Envelope>
    }

    void getResponse()
    {


        // Get the response, check for error.
        const QtSoapMessage &resp = http.getResponse();
        if (resp.isFault()) {
        //resultView->setHtml(tr("<b>Query failed</b>: ") + resp.faultString().value().toString());
        return;
        }

        // Extract the return value from this method response, check for
        // errors.
        const QtSoapType &res = resp.returnValue();
        if (!res.isValid()) {
        //resultView->append(tr("Invalid return value"));
        return;
        }

        // Generate resultView output. Make it resemble the actual web
        // output from http://www.google.com/.
        QString header(tr("Searched the web for <b>%1</b>, results %2 - %3 "
                  "of about %4. Search took %5 seconds.<br><hr>")
               .arg(res["searchQuery"].toString())
               .arg(res["startIndex"].toInt())
               .arg(res["endIndex"].toInt())
               .arg(res["estimatedTotalResultsCount"].toInt())
               .arg(res["searchTime"].value().toDouble(), 0, 'f', 2));

        const QtSoapType &resultElements = res["resultElements"];
        QString allElements;

        for (int i = 0; i < resultElements.count(); ++i) {
        const QtSoapType &resultElement = res["resultElements"][i];

        QString cat = resultElement["directoryCategory"]["fullViewableName"].toString();
        QString summary = resultElement["summary"].toString();
        QString title = resultElement["title"].toString();
        QString snippet = resultElement["snippet"].toString();
        QString url = resultElement["URL"].toString();
        QString cachedSize = resultElement["cachedSize"].toString();

        QString thisElement = "<br>";

        if (!title.isEmpty()) {
            thisElement += "<font color=\"#0000FF\"><b><u>"
                   + title + "</u></b></font><br>";
        } else {
            thisElement += "<font color=\"#0000FF\"><b><u>"
                   + url + "</u></b></font><br>";
        }

        if (!snippet.isEmpty())
            thisElement += snippet + "<br>";

        if (!summary.isEmpty()) {
            thisElement += "<font color=\"#808080\">Description:</font> "
                   + summary + "<br>";
        }

        if (!cat.isEmpty()) {
            thisElement += "<font color=\"#808080\">Category: <u>"
                   + cat + "</u></font><br>";
        }

        if (!title.isEmpty()) {
            thisElement += "<font color=\"#008000\"><u>" + url
                   + "</u> - " + cachedSize + "</font><br>";
        }

        allElements += thisElement;
        }

        // Update the resultView.
        QString s = (header + allElements);
        qDebug() << s;
    }

};

#endif // XMLAPI_H
