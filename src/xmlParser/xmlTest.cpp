/**
 ****************************************************************************
 * <P> XML.c - XML parser test example - char* version </P>
 *
 * @version     V2.43
 * @author      Frank Vanden Berghen
 *
 * Copyright (c) 2002, Business-Insight
 * All rights reserved.
 * See the file "AFPL-license.txt" about the licensing terms
 *
 ****************************************************************************
 */
#ifdef WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdio.h>
#include "xmlParser.h"

void myfree(char *t); // {free(t);}
ToXMLStringTool tx,tx2;

int main(int argc, char **argv)
{
    ///////////////////////////////////////////////////////////////////////////////////
    //                                                                               //
    //    Example 1: Basic operations to parse and collect data from a XML file      //
    //                                                                               //
    ///////////////////////////////////////////////////////////////////////////////////

    printf("EXAMPLE 1\n");

    // this open and parse the XML file:
    XMLNode xMainNode=XMLNode::openFileHelper("PMMLModel.xml","PMML");

    // this prints "RANK For <you>":
    XMLNode xNode=xMainNode.getChildNode("Header");
    printf("  Application Name is: '%s' (note that &lt; has been replaced by '<')\n", xNode.getChildNode("Application").getAttribute("name"));

    // this prints "Hello World!"
    printf("  Text inside Header tag is :'%s'\n", xNode.getText());

    // this prints "urn"
    printf("  Value of the first attribute of the 'PMML/Extension/Key' tag is :'%s'\n", xMainNode.getChildNodeByPath("Extension/Key").getAttributeValue());
    // The code:
    // xMainNode.getChildNodeByPath("A/B/C/D")
    // ... is equivalent (but slower) to:
    // xMainNode.getChildNode("A").getChildNode("B").getChildNode("C").getChildNode("D")

    // this gets the number of "NumericPredictor" tags:
    xNode=xMainNode.getChildNode("RegressionModel").getChildNode("RegressionTable");
    int n=xNode.nChildNode("NumericPredictor");

    // this prints the "coefficient" value for all the "NumericPredictor" tags:
    int i,myIterator=0;
    for (i=0; i<n; i++)
        printf("    coeff %i=%s\n",i+1,xNode.getChildNode("NumericPredictor",&myIterator).getAttribute("coefficient"));

    // this create a file named "test.xml" based on the content of the first "Extension" tag of the XML file:
    xMainNode.getChildNode("Extension").writeToFile("test.xml","ISO-8859-1");

    printf("  The content of the clear tag is:%s\n",xMainNode.getChildNode("html_page").getClear().lpszValue);

    ///////////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                           //
    //    Example 2: memory management: when to use the 'stringDup' and the 'free' functions     //
    //                                                                                           //
    ///////////////////////////////////////////////////////////////////////////////////////////////

    printf("EXAMPLE 2\n");

    // compare these 4 lines ...
    char *t=stringDup(xMainNode.getAttribute("version")); // get version number
    xMainNode=XMLNode::emptyNode();                       // free from memory the top of the xml Tree
    printf("  PMML Version :%s\n\n",t);                       // print version number
    myfree(t);                                              // free version number

    // ... with the following 3 lines (currently commented, because of error):
    //  t=xMainNode.getAttribute("version");      // get version number (note that there is no 'stringDup')
    //  xMainNode=XMLNode::emptyXMLNode;          // free from memory the top of the xml Tree AND the version number inside the 't' var
    //  printf("PMML Version :%s\n",t);           // since the version number in 't' has been free'd, this will not work

    /////////////////////////////////////////////////////////////////
    //                                                             //
    //    Example 3: constructing & updating a tree of XMLNode     //
    //                                                             //
    /////////////////////////////////////////////////////////////////

    printf("EXAMPLE 3\n");

    // We create in memory from scratch the following XML structure:
    //  <?xml version="1.0"?>
    //      <body color="FFFFFF"> Hello universe. </body>
    //      <A><B><C>pick-a-boo</C></B></A>
    // ... and we transform it into a standard C string that is printed on screen.
    xMainNode=XMLNode::createXMLTopNode("xml",TRUE);
    xMainNode.addAttribute("version","1.0");
    xNode=xMainNode.addChild("body");
    xNode.addText("Hello \"univ\"!");
    xNode.deleteText();
    xNode.addText("Hello \"universe\"!");
    xNode.addAttribute("color","#wrongcolor");
    xNode.updateAttribute("#FFFFFF",NULL,"color");
    xMainNode.getChildNodeByPath("A.B.C",true,'.').addText("pick-a-boo");

    t=xMainNode.createXMLString(false);
    printf("  XMLString created from scratch:\n   %s",t);
    myfree(t);

    // we delete some parts:
    xNode.deleteAttribute("color");
    xMainNode.getChildNode("A").deleteNodeContent();
    t=xMainNode.createXMLString(false);
    printf("\n  With the \"A\" tag deleted and the \"color\" attribute deleted:\n   %s\n\n",t);
    myfree(t);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                                            //
    //    Example 4: by default, the XML parser is "forgiving" with respect to errors inside XML strings&files    //
    //                                                                                                            //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    printf("EXAMPLE 4\n");

    // By default, the XML parser is "forgiving":
    // (You can de-activate this behavior: see the header of the xmlParser.cpp file)
    const char *t2="<a><b>some text</b><b>other text    </a>";
    XMLResults xe;
    xMainNode=XMLNode::parseString(t2,NULL,&xe);
    t=xMainNode.createXMLString(false);
    printf("  The following XML: %s\n    ...is parsed as: %s\n  with the following info: '%s'\n\n",t2,t?t:"(null)",XMLNode::getError(xe.error));
    myfree(t);

    /////////////////////////////////////////////////////////////
    //                                                         //
    //    Example 5: deleting a part of the tree of XMLNode    //
    //                                                         //
    /////////////////////////////////////////////////////////////

    printf("EXAMPLE 5\n");

    // this deletes the "<b>other text</b>" subtree part:
    xMainNode.getChildNode("b",1).deleteNodeContent();

    // To perform the same "delete" as above, we can also do:
    // xNode=xMainNode.getChildNode("a").getChildNode("b",1); xNode.deleteNodeContent(); xNode=XMLNode::emptyXMLNode;
    // If you forget the last part of the delete ("xNode=XMLNode::emptyXMLNode"), then the XMLNode will NOT be deleted:
    // In this case, as long as there exists a reference to the XMLNode, the smartPointer mechanism prevent the node to be deleted.

    // To perform the same "delete" as above, we can also do:
    // xNode=xMainNode.getChildNode("a").getChildNode("b",1); xNode.deleteNodeContent(true);
    // The "true" parameter will force the deletion, even if there still exists some references to the XMLNode.
    // This is however very dangerous because, after the delete, the xNode object is invalid and CANNOT be used anymore.
    // Unexpected results may appear if you still try to access the xNode object after its "forced" deletion.

    t=xMainNode.createXMLString(false);
    printf("  ...with the wrong node deleted: %s\n\n",t);
    myfree(t);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                                             //
    //   Example 6: inserting (and moving) a new XMLNode in the middle of an already existing XMLNode structure    //
    //                                                                                                             //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    printf("EXAMPLE 6\n");

    // This creates a XMLNode 'a' that is "<a><b>some text</b><b>other text</b></a>":
    xMainNode=XMLNode::parseString(t2);
    // This creates a XMLNode 'c' that is "<c>hello</c>":
    xNode=XMLNode::parseString("<c>hello</c>");

    xMainNode.addChild(xNode,0);
    t=xMainNode.createXMLString(false);
    printf("  We inserted a new node 'c' as the first tag inside 'a':\n       %s",t);
    myfree(t);

    xMainNode.addChild(xNode,xMainNode.positionOfChildNode("b",1));
    t=xMainNode.createXMLString(false);
    printf("\n  We moved the node 'c' at the position of the second 'b' tag:\n       %s\n\n",t);
    myfree(t);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                                             //
    //   Example 7: enumerate all the content of a xmlNode in the order in which they appear inside the XML        //
    //                                                                                                             //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    printf("EXAMPLE 7\n");

    printf("  Enumeration of the content of the HEADER tag inside the PMML file:\n");
    xMainNode=XMLNode::openFileHelper("PMMLModel.xml","PMML").getChildNode("Header");

    XMLElementPosition ii=xMainNode.nAttribute(),   // we don't want to list all the attributes
                       nn=xMainNode.nElement();     // there are in total nElement.
    while (ii<nn)
    {
        XMLNodeContents xnc=xMainNode.enumContents(ii);
        printf("    Element %i is ",ii);
        switch(xnc.etype)
        {
        case eNodeNULL:
        case eNodeAttribute: break; // in this example we skip the attributes
        case eNodeChild: printf("a childNode named '%s'\n",xnc.child.getName()); break;
        case eNodeText : printf("a text '%s'\n",xnc.text); break;
        case eNodeClear: printf("a '%s' clear Tag\n",xnc.clear.lpszOpenTag);
        }
        ii++;
    }

    ////////////////////////////////////////////////
    //                                            //
    //    Example 8: base 64 encoding/decoding    //
    //                                            //
    ////////////////////////////////////////////////

    printf("\nEXAMPLE 8\n");

    unsigned char *originalBinaryData=(unsigned char *)"this is binary data.";
    XMLParserBase64Tool b64;
    t=b64.encode(originalBinaryData,21);
    printf(
      "  To be able to include any binary data into an xml file, some Base64"
      "\n  conversion functions (binary data <--> ascii/utf8 text) are provided:\n"
      "    original binary data   : %s\n"
      "    encoded as text        : %s\n",originalBinaryData,t);
    printf("    decoded as binary again: %s\n\n",b64.decode(t));

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //    Example 9: demonstration of multi-lingual XML file parsing    //
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    printf("EXAMPLE 9\n");
    printf("  Processing XML file containing chinese,cyrilic and other extended characters.\n");
    xMainNode=XMLNode::openFileHelper("utf8test.xml");
    xMainNode.writeToFile("outputTestUTF8.xml");
    printf("  ... resulting multi-lingual file is 'outputTestUTF8.xml'.\n\n");

    ////////////////////////////////////////////////////////////
    //                                                        //
    //    Example 10: usage of the "getParentNode()" method    //
    //                                                        //
    ////////////////////////////////////////////////////////////

    printf("EXAMPLE 10\n");
    printf("  Two examples of usage of the \"getParentNode()\" method:\n");
    // In the following two examples, I create a tree of XMLNode based on the string
    // "<a><b>some text</b><b>other text</b></a>". After parsing this string
    // I get a XMLNode that represents the <a> tag. Thereafter I "go down" one
    // level, using getChildNode: I now have a XMLNode that represents the <b> tag.
    // Thereafter I "go up" one level, using getParentNode(): I now have once again
    // a XMLNode that represents the <a> tag. Thereafter, I print the name ('a') of
    // this last XMLNode. The first example below is working as intended (it prints 'a'
    // on the screen). However, the second example below prints "null" because when we
    // did "xMainNode=xMainNode.getChildNode()" we lost all references to the
    // top node and thus it's automatically "garbage collected" (free memory).
    xMainNode=XMLNode::parseString(t2);     xNode=xMainNode.getChildNode();         xNode=xNode.getParentNode(); t=(char*)    xNode.getName(); printf("   Ex1: Name of top node; '%s'\n",t?t:"null");
    xMainNode=XMLNode::parseString(t2); xMainNode=xMainNode.getChildNode(); xMainNode=xMainNode.getParentNode(); t=(char*)xMainNode.getName(); printf("   Ex2: Name of top node; '%s'\n",t?t:"null");


    //////////////////////////////////////////////////////////
    //                                                      //
    //    Example 11: usage of the ToXMLStringTool class    //
    //                                                      //
    //////////////////////////////////////////////////////////

    printf("\nEXAMPLE 11\n");
    // For performance reason it's sometime better to use the old-style "fprintf"
    // function to create a XML file directly without constructing first
    // a XMLNode structure. In such case, the ToXMLStringTool class comes in handy.

    const char *t3="Hello to the <\"World\">";
    printf("  ToXMLStringTool demo: Original String: %s\n"
           "                        Encoded in XML : %s\n",t3,ToXMLStringTool().toXML(t3));

    // If you use several time (in different "fprintf") the same instance of
    // the ToXMLStringTool class, then the memory allocation (needed to create the output
    // buffer) will be performed only once. This is very efficient, very fast.
    // Usually, I create a global instance of the ToXMLStringTool class named "tx" (see
    // line 44 of this file) and then I use "tx" everywhere. For example:
    const char *t4="I say 'pick-a-boo'!";
    printf("  Global ToXMLStringTool: %s\n",tx.toXML(t4));
    printf("  Global ToXMLStringTool: %s\n",tx.toXML(t3));

    // However you must be careful because sometime the output buffer might be
    // erased before being printed. The next example is not working:
    printf("  Error using ToXMLStringTool: %s\n"
           "                               %s\n",tx.toXML(t4),tx.toXML(t3));

    // However, this is working fine:
    printf("  Correct usage of ToXMLStringTool: %s\n"
           "                                    %s\n",tx.toXML(t4),tx2.toXML(t3));

    // Using the "ToXMLStringTool class" and the "fprintf function" is THE most efficient
    // way to produce VERY large XML documents VERY fast.

    return 0;
}

#ifdef _USE_XMLPARSER_DLL
    // We are using the DLL version of the XMLParser library.
    // NOTE: With visual studio .NET, you can always use the standard "free()" function: You don't
    //       need a special "DLL free" version.
    void myfree(char *t){freeXMLString(t);}
#else
    // we are using the normal, classical version of the XMLParser library (directly from C++ sources)
    void myfree(char *t){free(t);}
#endif
