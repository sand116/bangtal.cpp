#include <bangtal>
#include <string>

using namespace bangtal;
using namespace std;

class Item : public Object //오브젝트 상속
{
public:// create함수를 호출하여 객체 생성할 수 있음 -> sharedpointer인 objectPtr로 반환하여 shared_pointer로 접근할 수 있도록함
    static ObjectPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0, bool shown = true) {
        auto object = ObjectPtr(new Item(image, scene, x, y, shown)); //ojbectPtr주소에 넣은 객체 - 내부에서 생성
        Object::add(object);//이벤트를 받을 object 리스트에 추가해야, 방탈 내부적으로 이벤트를 받기 위해서 객체를 찾아낼 수 있음. 
        return object; //object 포인터를 반환
    }
protected: // 생성자를 protect 안에 넣어, 외부에서 new로 생성되지 못하도록 함 new Item() 으로 생성될 수 없음-> 스마트포인터로 메모리 관리 
    Item(const string& image, ScenePtr scene, int x, int y, bool shown) : Object(image, scene, x, y, shown) {}
    //생성자 파라미터는 원하는 대로 정의할 수 있음
public:
    //가상함수 -> 재정의할 함수 
    virtual bool onMouse(int x, int y, MouseAction action) {
        //Object::onMouse 아이템을 줍는다
        //기본형식 멤버에 접근s
        if (!Object::onMouse(x, y, action)) {
            Object::pick();
        }
        return true;
    }
};