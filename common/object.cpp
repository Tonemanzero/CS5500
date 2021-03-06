#include "object.h"
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

// TemplateObject functions

TemplateObject::TemplateObject(
  string nam, int hp, int str, int wei, bool isFire, bool isWet)
{
  name = nam;
  baseHp = hp;
  strength = str;
  weight = wei;
  isFlamable = isFire;
  isWetable = isWet;
}
string TemplateObject::getName() const
{
  return name;
}
int TemplateObject::getHp() const
{
  return baseHp;
}
int TemplateObject::getStrength() const
{
  return strength;
}
int TemplateObject::getWeight() const
{
  return weight;
}
bool TemplateObject::getIsFlamable() const
{
  return isFlamable;
}
bool TemplateObject::getIsWetable() const
{
  return isWetable;
}

// TemplateObjectList static variables
std::mutex TemplateObjectList::creationLock;
TemplateObjectList* TemplateObjectList::pInstance;

// TemplateObjectList functions

TemplateObjectList* TemplateObjectList::getInstance()
{
  if (pInstance == nullptr)
  {
    // Enter critical section
    std::lock_guard<std::mutex> lock(creationLock);
    if (pInstance == nullptr)
    {
      pInstance = new TemplateObjectList();
    }
  }

  return pInstance;
}

int TemplateObjectList::getSize() const
{
  return list.size();
}
int TemplateObjectList::addTemplate(TemplateObject temp)
{
  list.push_back(temp);
  return list.size() - 1;
}
const TemplateObject TemplateObjectList::getTemplate(unsigned int i) const
{
  if (i < list.size())
    return list[i];
  else
  {
    throw std::invalid_argument(
      "Error: index out of bounds when accessing the ObjectList.");
  }
}
int TemplateObjectList::findTemplate(string name) const
{
  for (unsigned int i = 0; i < list.size(); i++)
  {
    if (name == list[i].getName()) return i;
  }
  return -1;
}

// Object functions
Object::Object()
{
  id = -1;
  hp = 0;
  strength = 0;
  weight = 0;
  stateFire = 0;
  stateWet = 0;
}
Object::Object(int i, int h, int str, int wei, bool isfire, bool iswet)
{
  id = i;
  hp = h;
  strength = str;
  weight = wei;
  stateFire = isfire;
  stateWet = iswet;
}
Object::Object(int templateId)
{
  TemplateObject temp = TemplateObjectList::getInstance()->getTemplate(id);
  id = templateId;
  // Look up the starting hp from out template
  hp = temp.getHp();
  strength = temp.getStrength();
  weight = temp.getWeight();
  stateFire = 0;
  stateWet = 0;
}

int Object::getId() const
{
  return id;
}
int Object::getHp() const
{
  return hp;
}
int Object::getStrength() const
{
  return strength;
}
int Object::getWeight() const
{
  return weight;
}
bool Object::getStateFire() const
{
  return stateFire;
}
bool Object::getStateWet() const
{
  return stateWet;
}
bool Object::getFlamable() const
{
  return TemplateObjectList::getInstance()->getTemplate(id).getIsFlamable();
}
bool Object::getWetable() const
{
  return TemplateObjectList::getInstance()->getTemplate(id).getIsWetable();
}

void Object::setHp(int i)
{
  hp = i;
}
void Object::setStrength(int i)
{
  strength = i;
}
void Object::setWeight(int i)
{
  weight = i;
}
void Object::setStateFire(bool i)
{
  stateFire = i;
}
void Object::setStateWet(bool i)
{
  stateWet = i;
}
