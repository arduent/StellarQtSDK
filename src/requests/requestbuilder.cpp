#include "requestbuilder.h"
#include "../server.h"


RequestBuilder::RequestBuilder(Server *server, QString defaultSegment):m_streamMode(false){
    m_server=server;
    m_uri = server->serverURI();
    if(!defaultSegment.isEmpty()){
        m_segmentsAdded=false;//initialization... setSegments requires it.
        this->setSegments(defaultSegment);
    }
    m_segmentsAdded = false; // Allow overwriting segments
}

RequestBuilder::~RequestBuilder()
{

}

Server *RequestBuilder::server(){
    return m_server;
}

bool RequestBuilder::streamMode(){
    return m_streamMode;
}

void RequestBuilder::setStreamMode()
{
    m_streamMode=true;
}

RequestBuilder &RequestBuilder::setSegments(QString segment){
    return setSegments(QStringList() << segment);
}

RequestBuilder &RequestBuilder::setSegments(QStringList segments) {
    if (m_segmentsAdded) {
        throw std::runtime_error("URL segments have been already added.");
    }
    m_segmentsAdded = true;
    this->m_segments = segments;
    return *this;

}

void RequestBuilder::addParameter(QString key, QString value)
{
    m_queries.append(std::pair<QString,QString>(key,value));
}

RequestBuilder &RequestBuilder::cursor(QString cursor) {
    m_queries.append(std::pair<QString,QString>("cursor",cursor));
    return *this;
}

RequestBuilder &RequestBuilder::limit(int number) {
    m_queries.append(std::pair<QString,QString>("limit",QString::number(number)));
    return *this;
}

RequestBuilder &RequestBuilder::order(RequestBuilder::Order direction) {
    m_queries.append(std::pair<QString,QString>("order",this->toString(direction)));
    return *this;
}

RequestBuilder &RequestBuilder::asc(){
    return order(RequestBuilder::Order::ASC);
}

RequestBuilder &RequestBuilder::desc(){
    return order(RequestBuilder::Order::DESC);
}


QUrl RequestBuilder::buildUri() {
    QString base = this->m_uri.toString();

    QUrlQuery query(m_uri);
    for(auto q : this->m_queries){
        query.addQueryItem(std::get<0>(q),std::get<1>(q));
    }

    QStringList urlParts;
    urlParts.append(base);
    if(m_segments.isEmpty())
        urlParts.append(QString());//so / is added, just to end up with / at the end
    else
        urlParts.append(m_segments);
    QString path = urlParts.join("/");
    if(!query.isEmpty()){
        path.append("?");
        path.append(query.toString());
    }
    QUrl uri(path);
    if(uri.isValid()){
        this->setRequestUri(uri);
        return uri;
    }
    throw new std::runtime_error("invalid uri");

}

void RequestBuilder::setRequestUri(QUrl &uri)
{
    m_requestUri = uri;
}

QUrl& RequestBuilder::requestUri(){
    return this->m_requestUri;
}

QString RequestBuilder::toString(RequestBuilder::Order order)
{
    if(order== Order::ASC)
        return QString("asc");
    return QString("desc");
}

RequestBuilder::Order RequestBuilder::orderFromString(QString s)
{
    if(s==QString("asc"))
        return Order::ASC;
    return Order::DESC;
}
