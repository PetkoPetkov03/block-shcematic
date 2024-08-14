#include "./container.hpp"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <raylib.h>
#include <string>
#include <vector>

Link::Link(int pid, int sid) {
    this->pid = pid;
    this->sid = sid;
}

Link::~Link() {
    delete this;
}


Container::Container(int id, std::string content, int fontSize) {
    this->id = id;
    this->content = content;
    this->position = Vector2{10, 10};
    this->size = Vector2{300, 150};
    this->fontSize = fontSize;
    SetContentSize(MeasureText(GetContent().c_str(), GetFontSize()));
}

Container::~Container() {
  delete this;
}

int Container::GetFontSize(void) {
    return this->fontSize;
}

void Container::SetFontSize(int size) {
    this->fontSize = size;
}

int Container::GetContentSize(void) {
    return this->contentSize;
}

void Container::SetContentSize(int size) {
    this->contentSize = size;
}

int Container::GetId() {
  return this->id;
}

void Container::AddLink(Link* link) {
  this->links.push_back(*link);
}

void Container::AddLinks(std::vector<Link>* links) {
  this->links = *links;
}

std::vector<Link> Container::GetLinks() {
  return this->links;
}

std::string Container::GetContent() {
  return this->content;
}

Vector2 Container::GetPosition() {
  return this->position;
}

void Container::SetPosition(Vector2* position) {
  this->position = *position;
}

void Container::SetPosition(int x, int y) {
  Vector2 position;
  position.x = x;
  position.y = y;
}

Link Container::GetLinkById(int i) {
    Link link = this->links[i];
    
    return link;
}

Vector2 Container::GetSize() {
  return this->size;
}

void Container::SetSize(Vector2 size) {
  this->size = size;
}

void Container::SetSize(float width, float height) {
  this->size = Vector2{width, height};
}


Link Container::FindLink(Link* link) {
  std::vector<Link>::iterator it;

  it = std::find(this->links.begin(), this->links.end(), *link);

  if(it == this->links.end()) {
    std::cout << "Link not found!" << std::endl;
    return Link(-1, -1);
  }

  return *it;
}


void Container::Draw() {
    Rectangle body = Rectangle{GetPosition().x, GetPosition().y, GetSize().x, GetSize().y};
    DrawRectangleRec(body, RED);

    DrawText(GetContent().c_str(), (body.x - (float)GetContentSize()/2) + (body.width / 2) ,
        (body.y - ((float)GetContentSize()/4)) + (body.height / 2) , GetFontSize(), GREEN);
}
