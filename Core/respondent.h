#pragma once
#include <string>
#include <iostream>

using namespace std;


class Respondent
{
private:
  int _age;
  double _hpd; //hours per day
  int _musician;
  int _frequency;
  int _anxiety;
  int _depression;
  int _insomnia;
  int _ocd;
  int _effect;

public:
  Respondent(int age, double hpd, int musician, int frequency, int anxiety, int depression,
             int insomnia, int ocd, int effect)
             : _age(age), _hpd(hpd), _musician(musician), _frequency(frequency),
               _anxiety(anxiety), _depression(depression), _insomnia(insomnia),
               _ocd(ocd), _effect(effect) {};
  ~Respondent() {};

  int GetAge() const {
    return _age;
  }
  double GetHpd() const {
    return _hpd;
  }
  int GetMusician() const {
    return _musician;
  }
  int GetFrequency() const {
    return _frequency;
  }
  int GetAnxiety() const {
    return _anxiety;
  }
  int GetDepression() const {
    return _depression;
  }
  int GetInsomnia() const {
    return _insomnia;
  }
  int GetOcd() const {
    return _ocd;
  }
  int GetEffect() const {
    return _effect;
  }

  void SetAge(int& age) {
    this->_age = age;
  }
  void SetHpd(double& hpd) {
    this->_hpd = hpd;
  }
  void SetMusician(int& musician) {
    this->_musician = musician;
  }
  void SetFrequency(int& frequency) {
    this->_frequency = frequency;
  }
  void SetAnxiety(int& anxiety) {
    this->_anxiety = anxiety;
  }
  void SetDepression(int& depression) {
    this->_depression = depression;
  }
  void SetInsomnia(int& insomnia) {
    this->_insomnia = insomnia;
  }
  void SetOcd(int& ocd) {
    this->_ocd = ocd;
  }
  void SetEffect(int& effect) {
    this->_effect = effect;
  }

  friend ostream& operator<<(ostream& out, const Respondent& respondent);
};


ostream& operator<<(ostream& out, const Respondent& respondent)
{
  out << "Age: " << respondent.GetAge() << '\n';
  out << "Hpd: " << respondent.GetHpd() << '\n';
  out << "Musician: " << respondent.GetMusician() << '\n';
  out << "Frequency: " << respondent.GetFrequency() << '\n';
  out << "Anxiety: " << respondent.GetAnxiety() << '\n';
  out << "Depression: " << respondent.GetDepression() << '\n';
  out << "Insomnia: " << respondent.GetInsomnia() << '\n';
  out << "OCD: " << respondent.GetOcd() << '\n';
  out << "Effect: " << respondent.GetEffect() << '\n';
  out << '\n';

  return out;
}
