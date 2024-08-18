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

Container::Container(enum Behaviour behaviour, int id, std::string content, int fontSize) {
    this->behaviour = behaviour;
    this->id = id;
    this->content = content;
    this->position = Vector2{10, 10};
    Rectangle body;
    body.x = 10;
    body.y = 10;
    body.width = 300;
    body.height = 150;
    SetBody(&body);
    this->size = Vector2{300, 150};
    this->fontSize = fontSize;
    SetContentSize(MeasureText(GetContent().c_str(), GetFontSize()));
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
    DrawRectangleRec(GetBody(), RED);

    DrawText(GetContent().c_str(), (GetBody().x - (float)GetContentSize()/2) + (GetBody().width / 2) ,
        (GetBody().y - ((float)GetContentSize()/4)) + (GetBody().height / 2) , GetFontSize(), GREEN);
}


Rectangle Container::GetBody(void) {
    return this->body;
}

void Container::SetBody(Rectangle* body) {
  this->body = *body;
}
