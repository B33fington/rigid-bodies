#include "precompiled.h"

void Scene::checkCollisions()
{
    for (std::vector<RigidBody *>::iterator itA = _bodies.begin() ; itA != _bodies.end(); ++itA) {
        for (std::vector<RigidBody *>::iterator itB = _bodies.begin() ; itB != _bodies.end(); ++itB) {
            // Do not continue if they are the same object
            if (itA == itB) continue;

            Collision *collision = new Collision(*itA, *itB);
            std::cout << "IS IT WORKING YET" << std::endl;
            CollisionPair *cp = collision->dispatcher();
            std::cout << "IS IT WORKING YET, STILL?" << std::endl;
            if (cp != NULL) {
                _collisions.push_back(cp);
            }
        }
    }
}

// Not sure if we need this.
void Scene::getImpulse()
{
    for(std::vector<CollisionPair *>::iterator it = _collisions.begin() ; it != _collisions.end(); it++){
        (*it)->CollisionPair::applyImpulse();
        //std::cout << "velocity A: " << (*it)->_A->_velocity[1] << std::endl;
        //std::cout << "collisions: " << (*it)->_collisions[0][0] << "   " << (*it)->_collisions[0][1] << std::endl;

    }
}

void Scene::applyG()
{
    float dt = 0.01667;
    for (std::vector<RigidBody *>::iterator it = _bodies.begin() ; it != _bodies.end(); ++it) {
        if ( (*it)->_isStatic ) continue;

        (*it)->_velocity += glm::vec2(0, GRAVITATIONAL_FORCE) * dt / (*it)->_mass;
        (*it)->_angularVelocity += ((*it)->_torque * dt / (*it)->_momentOfInertia);
        std::cout << "ang Vel: " << (*it)->_velocity[1] << std::endl;
    }
}

// Do not think we need this.
void Scene::integrateAcceleration()
{
    // TODO
}

void Scene::integrateVelocities()
{
    float dt = 0.01667;
    for (std::vector<RigidBody *>::iterator it = _bodies.begin() ; it != _bodies.end(); ++it) {
        (*it)->_position += (*it)->_velocity * dt;

        //std::cout << "velo: " << (*it)->_velocity[1] << std::endl;
        //std::cout << "pos:  " << (*it)->_orientation << std::endl;
        (*it)->_orientation += (*it)->_angularVelocity * dt;
    }
}

void Scene::updatePositions()
{
    // TODO
}

void Scene::step()
{
    checkCollisions();
    applyG();
    integrateAcceleration();
    getImpulse();
    integrateVelocities();
    updatePositions();
    clearStep();
}

void Scene::clearStep()
{
    _collisions.clear();
}

void Scene::draw()
{
    for (std::vector<RigidBody *>::iterator it = _bodies.begin() ; it != _bodies.end(); ++it) {
        (*it)->_shape->draw();
    }
}

void Scene::addBody(RigidBody *rb)
{
    _bodies.push_back(rb);
}
