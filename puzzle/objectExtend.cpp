#include <bangtal>
#include <string>

using namespace bangtal;
using namespace std;

class Item : public Object //������Ʈ ���
{
public:// create�Լ��� ȣ���Ͽ� ��ü ������ �� ���� -> sharedpointer�� objectPtr�� ��ȯ�Ͽ� shared_pointer�� ������ �� �ֵ�����
    static ObjectPtr create(const string& image, ScenePtr scene = nullptr, int x = 0, int y = 0, bool shown = true) {
        auto object = ObjectPtr(new Item(image, scene, x, y, shown)); //ojbectPtr�ּҿ� ���� ��ü - ���ο��� ����
        Object::add(object);//�̺�Ʈ�� ���� object ����Ʈ�� �߰��ؾ�, ��Ż ���������� �̺�Ʈ�� �ޱ� ���ؼ� ��ü�� ã�Ƴ� �� ����. 
        return object; //object �����͸� ��ȯ
    }
protected: // �����ڸ� protect �ȿ� �־�, �ܺο��� new�� �������� ���ϵ��� �� new Item() ���� ������ �� ����-> ����Ʈ�����ͷ� �޸� ���� 
    Item(const string& image, ScenePtr scene, int x, int y, bool shown) : Object(image, scene, x, y, shown) {}
    //������ �Ķ���ʹ� ���ϴ� ��� ������ �� ����
public:
    //�����Լ� -> �������� �Լ� 
    virtual bool onMouse(int x, int y, MouseAction action) {
        //Object::onMouse �������� �ݴ´�
        //�⺻���� ����� ����s
        if (!Object::onMouse(x, y, action)) {
            Object::pick();
        }
        return true;
    }
};