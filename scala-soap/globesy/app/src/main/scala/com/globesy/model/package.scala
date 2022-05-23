package com.globesy

import java.time.ZonedDateTime
import java.time.temporal.ChronoUnit
import javax.xml.bind.annotation.{XmlAttribute, XmlElement}

// trick to allow classes being accessible from java code
package object model {}
package model {

  case class HourlyVal(temperature: Double, windSpeed: Double, timestamp: ZonedDateTime)

  case class DailyVal(hourly: Seq[HourlyVal])

  case class SoapResult(
                         windAvg: Double,
                         windMax: Double,
                         winMin: Double,
                         tempAvg: Double,
                         tempMax: Double,
                         tempMin: Double,
                         timestamp: Option[ZonedDateTime]
                       ) {
    @XmlAttribute(name = "ForDay")
    val time: String = timestamp.map(_.truncatedTo(ChronoUnit.DAYS).toLocalDate).getOrElse("").toString

    @XmlElement(name = "WindAverage")
    val wAvg = windAvg

    @XmlElement(name = "WindMaximum")
    val wmax = windMax

    @XmlElement(name = "WindMinimum")
    val wmin = winMin

    @XmlElement(name = "TempAverage")
    val tAvg = tempAvg

    @XmlElement(name = "TempMaximum")
    val tMax = tempMax

    @XmlElement(name = "TempMinimum")
    val tMin = tempMin
  }

}
