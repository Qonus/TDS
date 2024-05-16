#include "GameObjectManager.h"
#include "PhysicsManager.h"
#include "Input.h"

#include "GameObject.h"

GameObjectManager::GameObjectManager(Scene* _scene) : scene(_scene){

}

GameObjectManager::~GameObjectManager() {
    int size = objects.size();
    for (int i = 0; i < size; i++)
    {
        RemoveGameObjectAt(0);
    }
}

void GameObjectManager::HandleInput(sf::Event* event) {
    int i = 0;
    while (i < objects.size()) {
        objects[i]->HandleInput(event);
        i++;
    }
}

void GameObjectManager::FixedUpdateAll() {
    int i = 0;
    while (i < objects.size()) {
        objects[i]->FixedUpdate();
        i++;
    }
}

void GameObjectManager::UpdateAll() {
    int i = 0;
    while (i < objects.size()) {
        objects[i]->Update();
        i++;
    }
}

void GameObjectManager::DrawAll(sf::RenderWindow* window) {
    int i = 0;
    while (i < objects.size()) {
        objects[i]->Draw(window);
        i++;
    }

    i = 0;
    while (i < objects.size()) {
        objects[i]->DrawUI(window);
        i++;
    }
}


// Setters
GameObject* GameObjectManager::AddGameObject(GameObject* object, Transform transform) {
    object->getTransform()->position += transform.position;
    object->getTransform()->rotation += transform.rotation;
    object->getTransform()->scale = Math::multiplyVectors(transform.scale, object->getTransform()->scale);
    object->objectManager = this;
    object->copyIndex = GetGameObjectByName(object->getName()).size();
    object->Update();
    objects.emplace_back(object);
    Collider* collider = object->GetComponent<Collider>();
    Rigidbody* rigidbody = object->GetComponent<Rigidbody>();
    //std::cout << "ADD " << objects.size() << '\n';
    if (collider != nullptr && rigidbody != nullptr) {
        scene->getPhysics()->AddBody(new Body(rigidbody, collider));
    }
    return object;
}

void GameObjectManager::RemoveGameObject(GameObject* object) {
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i] == object) {
            RemoveGameObjectAt(i);
            return;
        }
    }
}

void GameObjectManager::RemoveGameObjectByName(std::string objectName, int objectCopyIndex) {
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->getName() == objectName && objects[i]->copyIndex == objectCopyIndex) {
            RemoveGameObjectAt(i);
            return;
        }
    }
}

void GameObjectManager::RemoveGameObjectAt(int objectIndex) {
    Collider* collider = objects[objectIndex]->GetComponent<Collider>();
    Rigidbody* rigidbody = objects[objectIndex]->GetComponent<Rigidbody>();
    if (collider != nullptr && rigidbody != nullptr) {
        scene->getPhysics()->RemoveBody(collider->getObject());
    }
    delete objects[objectIndex];
    objects[objectIndex] = nullptr;
    objects.erase(objects.begin() + objectIndex);
}

void GameObjectManager::RemoveAll() {
    for (int i = 0; i < objects.size(); i++)
    {
        RemoveGameObjectAt(i);
    }
}

// Getters
std::vector<GameObject*> GameObjectManager::GetGameObjectByName(std::string objectName) {
    std::vector<GameObject*> results;
    for (GameObject* object : objects)
    {
        if (object->getName() == objectName) {
            results.emplace_back(object);
        }
    }
    return results;
}

GameObject* GameObjectManager::GetGameObjectByIndex(int objectIndex) {
    return objects[objectIndex];
}

Scene* GameObjectManager::getScene() {
    return scene;
}