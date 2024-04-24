#include <string>
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
  Respondent(int _age, double _hpd, int _musician, int _frequency, int _anxiety, int _depression,
             int _insomnia, int _ocd, int _effect)
             : _age(_age), _hpd(_hpd), _musician(_musician), _frequency(_frequency),
               _anxiety(_anxiety), _depression(_depression), _insomnia(_insomnia),
               _ocd(_ocd), _effect(_effect) {};
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

  void SetAge(int age) {
    this->_age = age;
  }
  void SetHpd(double hpd) {
    this->_hpd = hpd;
  }
  void SetMusician(int musician) {
    this->_musician = musician;
  }
  void SetFrequency(int frequency) {
    this->_frequency = frequency;
  }
  void SetAnxiety(int anxiety) {
    this->_anxiety = anxiety;
  }
  void SetDepression(int depression) {
    this->_depression = depression;
  }
  void SetInsomnia(int insomnia) {
    this->_insomnia = insomnia;
  }
  void SetOcd(int ocd) {
    this->_ocd = ocd;
  }
  void SetEffect(int effect) {
    this->_effect = effect;
  }
};
