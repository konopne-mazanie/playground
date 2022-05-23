package com.globesy

import akka.actor.{ActorRef, ActorSystem, Props}
import akka.util.Timeout
import com.typesafe.scalalogging.StrictLogging

import scala.concurrent.{ExecutionContext, ExecutionContextExecutor}
import javax.xml.ws.Endpoint
import scala.concurrent.duration.DurationInt


object Runner extends App with StrictLogging {

  implicit val ec: ExecutionContextExecutor = ExecutionContext.global
  implicit val ac: ActorSystem = ActorSystem()
  implicit val timeout: Timeout = 10.seconds

  val appServiceActor: ActorRef = ac.actorOf(Props(new AppServiceActor(new RestService())))

  val endpoint = Endpoint.publish("http://localhost:8080/wstest", new SoapService(appServiceActor))
  ac.log.info("Server is running...")
}
