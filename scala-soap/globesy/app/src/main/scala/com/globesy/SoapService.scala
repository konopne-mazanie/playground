package com.globesy

import akka.Done
import akka.actor.ActorRef
import akka.pattern.ask
import akka.util.Timeout
import com.globesy.model.{DailyVal, Results}

import javax.jws.{WebMethod, WebParam, WebService}
import scala.concurrent.duration.Duration
import scala.concurrent.{Await, ExecutionContext}
import scala.jdk.CollectionConverters._

@WebService(serviceName = "Globesy")
class SoapService(private val appServiceActor: ActorRef)(implicit timeout: Timeout, ec: ExecutionContext) {

  @WebMethod(operationName = "forecast7d")
  def forecast7d(): Results =
    new Results(Await.result(
      ask(appServiceActor, AppServiceActor.GetForecast).mapTo[Done]
        .flatMap(_ => ask(appServiceActor, AppServiceActor.Forecast7d).mapTo[Option[Seq[(DailyVal, Int)]]]),
      Duration.Inf
    ).toList.flatMap(Computations.countForDays).asJava)

  @WebMethod(operationName = "forecast1d")
  def forecast1d(@WebParam(name="day") day: Int): Results =
    new Results(Await.result(
      ask(appServiceActor, AppServiceActor.GetForecast).mapTo[Done]
        .flatMap(_ => ask(appServiceActor, AppServiceActor.Forecast1d(day)).mapTo[Option[DailyVal]]),
      Duration.Inf
    ).toList.flatMap(forecastForDay => Computations.countForDays(Seq((forecastForDay, day)))).asJava)

}
