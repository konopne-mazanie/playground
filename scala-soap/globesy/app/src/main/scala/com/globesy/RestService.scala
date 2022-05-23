package com.globesy

import akka.actor.ActorSystem
import akka.http.scaladsl.{Http, HttpExt}
import akka.http.scaladsl.client.RequestBuilding.Get
import akka.http.scaladsl.model.{HttpRequest, HttpResponse}
import akka.util.ByteString
import com.globesy.RestService.WeatherRequest
import com.globesy.model.{DailyVal, HourlyVal}
import io.circe.parser

import java.time.{ZoneId, ZonedDateTime}
import scala.async.Async.{async, await}
import scala.concurrent.{ExecutionContext, Future}

class RestService(implicit ac: ActorSystem, ec: ExecutionContext) {
  private val client: HttpExt = Http()

  def getForecastFor7days: Future[Seq[(DailyVal, Int)]] = async {
    val response: HttpResponse = await(client.singleRequest(
      WeatherRequest(
        RestService.lat,
        RestService.long,
        Seq(WeatherRequest.HourlyVars.Temperature2m, WeatherRequest.HourlyVars.WindSpeed10m)
      ).compose(RestService.url)
    ))

    val responseBody: String = await(response.entity.dataBytes.runFold(ByteString(""))(_ ++ _).map(_.utf8String))

    val json = parser.parse(responseBody).toOption.get

    val hourlyVars = (json \\ "hourly").headOption.get

    val temperatures: Seq[Double] = (hourlyVars \\ WeatherRequest.HourlyVars.Temperature2m.name).headOption.get.as[Seq[Double]].toOption.get

    val windSpeeds: Seq[Double] = (hourlyVars \\ WeatherRequest.HourlyVars.WindSpeed10m.name).headOption.get.as[Seq[Double]].toOption.get

    val timestamps: Seq[ZonedDateTime] = (hourlyVars \\ "time").headOption.get.as[Seq[String]].toOption.get.map(str => ZonedDateTime.parse(str + ":00Z"))

    (
      for (((temperature, windSpeed), timestamp) <- temperatures.zip(windSpeeds).zip(timestamps))
        yield HourlyVal(temperature, windSpeed, timestamp)
    ).sortBy(_.timestamp).sliding(24, 24).map(DailyVal).toSeq.zipWithIndex
  }

}

object RestService {
  // Open-Meteo API URL
  private final val url: String = "https://api.open-meteo.com/v1"

  // Zilina location, could be parametrized
  private final val lat: Double = 49.2113
  private final val long: Double = 18.7192

  implicit val zonedDateTimeOrdering: Ordering[ZonedDateTime] =
    (x: ZonedDateTime, y: ZonedDateTime) => x.withZoneSameInstant(ZoneId.of("UTC")).compareTo(y.withZoneSameInstant(ZoneId.of("UTC")))

  case class WeatherRequest(
                             latitude: Double,
                             longitude: Double,
                             hourlyVars: Seq[WeatherRequest.HourlyVars]
                           ) {
    def compose(apiUrl: String): HttpRequest =
      Get(s"$apiUrl/forecast?latitude=$latitude&longitude=$longitude${if (hourlyVars.nonEmpty) s"&hourly=${hourlyVars.map(_.name).mkString(",")}" else ""}")
  }

  object WeatherRequest {
    sealed trait HourlyVars { val name: String }
    object HourlyVars {
      case object Temperature2m extends HourlyVars { override val name = "temperature_2m" }
      case object WindSpeed10m extends HourlyVars { override val name = "windspeed_10m" }
    }
  }
}
