#ifndef CONTAINER_H
#define CONTAINER_H

#include <raylib.h>
#include <string>
#include <vector>

enum Behaviour {
    STARTEND,
    NORMAL,
    FUNCTION,
    CONDITIONAL,
};

class Link {
    public:
        Link(int pid, int sid);

        bool operator==(const Link& other) const {
            return this->pid == other.pid && this->sid == other.sid;
        }

    private:
        int pid;
        int sid;
};

class Container {
    public:
        Container(enum Behaviour behaviour, int id, std::string content, int fontSize);

        bool operator==(const Container& other) const {
            return this->id == other.id;
        }

        int GetId();
        std::string GetContent(void);
        Vector2 GetPosition(void);
        void SetPosition(Vector2* position);
        void SetPosition(int x, int y);

        std::vector<Link> GetLinks(void);
        void AddLinks(std::vector<Link>* links);
        void AddLink(Link* link);

        Link GetLinkById(int i);

        Link FindLink(Link* link);

        Vector2 GetSize(void);

        void SetSize(Vector2 size);

        void SetSize(float width, float height);

        void Draw(void);

        int GetFontSize(void);

        void SetFontSize(int size);

        int GetContentSize(void);

        void SetContentSize(int size);

        Rectangle GetBody(void); 

        void SetBody(Rectangle* body); 

    private:
        enum Behaviour behaviour;
        int id;
        std::string content;
        Vector2 position;
        std::vector<Link> links;
        Vector2 size;
        int contentSize;
        int fontSize;
        Rectangle body;
};

#endif // !CONTAINER_H
