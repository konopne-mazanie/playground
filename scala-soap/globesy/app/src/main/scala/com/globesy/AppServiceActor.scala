package com.globesy

import akka.Done
import akka.actor.Actor
import akka.event.Logging
import com.globesy.AppServiceActor.{Forecast1d, Forecast7d, GetForecast, Init}
import com.globesy.model.DailyVal

import java.time.{ZoneId, ZonedDateTime}
import java.time.temporal.ChronoUnit
import scala.concurrent.Await
import scala.concurrent.duration.Duration

class AppServiceActor(private val restService: RestService) extends Actor {

  private val log = Logging(context.system, this)

  self ! Init

  override def receive: Receive = {
    case Init => context.become(initialized(None))
  }

  def initialized(currentForecast: Option[Seq[(DailyVal, Int)]]): Receive = {
    case GetForecast =>
      log.info("Getting current forecast")

      if (!currentForecast.exists(
        _.headOption.exists {
          case (dailyVal, day) =>
            (day == 0) &&
              dailyVal.hourly.exists(_.timestamp.truncatedTo(ChronoUnit.DAYS).isEqual(ZonedDateTime.now(ZoneId.of("UTC")).truncatedTo(ChronoUnit.DAYS)))
        }
      )) context.become(initialized(Some(Await.result(restService.getForecastFor7days, Duration.Inf))))
      sender() ! Done
    case Forecast7d => sender() ! currentForecast
    case Forecast1d(day) => sender() ! currentForecast.flatMap(_.find(_._2 == day).map(_._1))
    case _ => log.error("unknown message")
  }

}

object AppServiceActor {
  private case object Init

  sealed trait Ops
  case object GetForecast
  case object Forecast7d extends Ops
  case class Forecast1d(day: Int) extends Ops
}
