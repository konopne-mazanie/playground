package com.globesy.model;

import javax.xml.bind.annotation.*;
import java.util.List;

@XmlRootElement()
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "Results")
public class Results {

    @XmlElement(name = "Result")
    public SoapResult[] results;

    public Results(List<SoapResult> results) { this.results = results.toArray(new SoapResult[0]); }

    public Results() { this.results = new SoapResult[]{}; }
}
