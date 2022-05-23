#!/bin/bash

curl -X POST -H "Content-Type: text/xml" \
    -d '<s11:Envelope xmlns:s11="http://schemas.xmlsoap.org/soap/envelope/">
  <s11:Body>
    <ns1:forecast1d xmlns:ns1="http://globesy.com/">
      <day>2</day>
    </ns1:forecast1d>
  </s11:Body>
</s11:Envelope>' \
    http://localhost:8080/wstest