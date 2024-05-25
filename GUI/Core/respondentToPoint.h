#pragma once
#include "point.h"
#include "respondent.h"

const double AGE_WEIGTH = 0.5;
const double HPD_WEIGTH = 5;
const double MUSICIAN_WEIGTH = 100;
const double FREQUENCY_WEIGTH = 2;
const double ANXIETY_WEIGTH = 1;
const double DEPRESSION_WEIGTH = 1;
const double INSOMNIA_WEIGTH = 1;
const double OCD_WEIGTH = 1;
const double EFFECT_WEIGTH = 100;


Point respondentToPoint(const Respondent& respondent, int id)
{
  Point point = {0, 0, id};
  double x = 0;
  double y = 0;

  x += respondent.GetAge() * AGE_WEIGTH;
  x += respondent.GetHpd() * HPD_WEIGTH;
  x += respondent.GetMusician() * MUSICIAN_WEIGTH;
  x += respondent.GetFrequency() * FREQUENCY_WEIGTH;
  
  y += respondent.GetAnxiety() * ANXIETY_WEIGTH;
  y += respondent.GetDepression() * DEPRESSION_WEIGTH;
  y += respondent.GetInsomnia() * INSOMNIA_WEIGTH;
  y += respondent.GetOcd() * OCD_WEIGTH;
  y += respondent.GetEffect() * EFFECT_WEIGTH;

  point.SetX(x);
  point.SetY(y);

  return point;
};
