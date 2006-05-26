#include <iostream>
#include <musicbrainz3/webservice.h>
#include "xmlParser/xmlParser.h"

using namespace std;
using namespace MusicBrainz;

class MbXmlParser
{
public:

    MbXmlParser();
    
    void parse(std::string data);
    
protected:

    void createArtist(XMLNode node);
    
};

MbXmlParser::MbXmlParser()
{
}

string
getText(XMLNode node)
{
    string text;
    for (int i = 0; i < node.nText(); i++) 
        text += node.getText(i);
    return text;
}

Artist &
MbXmlParser::createArtist(XMLNode artistNode)
{
    string id = artistNode.getAttribute("id", 0);
    string type = artistNode.getAttribute("type", 0);
    Artist artist(id, type);
    cout << "id = " << id << endl;
    cout << "type = " << type << endl;
    for (int i = 0; i < artistNode.nChildNode(); i++) {
        XMLNode node = artistNode.getChildNode(i);
        string name = node.getName(); 
        cout << "  " << name << endl;
        if (name == "name") {
            artist.setName(getText(node));
        }
        else if (name == "sort-name") {
            artist.setSortName(getText(node));
        }
/*        else if (name == "disambiguation") {
            artist.setDisambiguation(getText(node));
        }
        else if (name == "life-span") {
            artist.setDisambiguation(getText(node));
        }*/
    }
    return artist;
}

void
MbXmlParser::parse(string data)
{
    XMLNode root = XMLNode::parseString(data.c_str(), "metadata");
    for (int i = 0; i < root.nChildNode(); i++) {
        XMLNode node = root.getChildNode(i);
        string name = node.getName(); 
        cout << name << endl;
        if (name == "artist") {
            Artist &artist = createArtist(node);
        }
    }
}

int
main()
{
    MbXmlParser parser;
    parser.parse("<?xml version=\"1.0\" encoding=\"UTF-8\"?><metadata xmlns=\"http://musicbrainz.org/ns/mmd-1.0#\"><artist id=\"2c948044-de63-401a-8671-1600ed0f69bd\" type=\"Person\"><name>Chloáš Agnew</name><sort-name>Agnew, Chloáš</sort-name></artist></metadata>");
    //WebService::init();
    //WebService ws;
    //ws.get("artist", "2c948044-de63-401a-8671-1600ed0f69bd");
    //WebService::cleanup();
    return 0;
}