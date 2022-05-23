package com.globesy

import com.globesy.model.{DailyVal, SoapResult}

object Computations {

  def countForDays(data: Seq[(DailyVal, Int)]): Seq[SoapResult] = data.map { case (dailyVal, _) =>
    val windSpeeds: Seq[Double] = dailyVal.hourly.map(_.windSpeed)
    val temperatures: Seq[Double] = dailyVal.hourly.map(_.temperature)

    SoapResult(
      windAvg = windSpeeds.sum / dailyVal.hourly.size,
      windMax = windSpeeds.max,
      winMin = windSpeeds.min,
      tempAvg = temperatures.sum / dailyVal.hourly.size,
      tempMax = temperatures.max,
      tempMin = temperatures.min,
      dailyVal.hourly.headOption.map(_.timestamp)
    )
  }

}
