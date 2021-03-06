package com.automatak.render.dnp3.enums

import com.automatak.render._


object TimeSyncMode {

  private val comments = List(
    "Determines what the master station does when it sees the NEED_TIME iin bit"
  )

  def apply(): EnumModel = EnumModel("TimeSyncMode", comments, EnumModel.UInt8, codes, Base10)

  private val codes = List(
    EnumValue("None", 0, "don't perform a time-sync"),
    EnumValue("SerialTimeSync", 1, "synchronize the outstation's time using the serial time sync procedure")
  )

}



