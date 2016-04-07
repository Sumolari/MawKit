//
//  FiniteTimeActions.cpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 21/02/16.
//
//

#include "FiniteTimeActions.hpp"

#include "Random.hpp"

namespace MK {
namespace Actions {

//------------------------------------------------------------------------------
// MARK: - RemoveFromParent
//------------------------------------------------------------------------------

RemoveFromParent::RemoveFromParent()
{
}

RemoveFromParent::~RemoveFromParent()
{
}

RemoveFromParent *RemoveFromParent::create( float duration )
{
	RemoveFromParent *action = new ( std::nothrow ) RemoveFromParent();
	action->initWithDuration( duration );
	action->autorelease();
	return action;
}

bool RemoveFromParent::initWithDuration( float duration )
{
	return cocos2d::ActionInterval::initWithDuration( duration );
}

RemoveFromParent *RemoveFromParent::clone() const
{
	auto a = new ( std::nothrow ) RemoveFromParent();
	a->initWithDuration( this->_duration );
	a->autorelease();
	return a;
}

RemoveFromParent *RemoveFromParent::reverse() const
{
	CCASSERT( false, "reverse() not supported in RemoveFromParent" );
	return nullptr;
}

void RemoveFromParent::startWithTarget( cocos2d::Node *target )
{
	cocos2d::ActionInterval::startWithTarget( target );
}

void RemoveFromParent::update( float time )
{
	if ( time > 0 && this->_target != nullptr ) {
		this->_target->removeFromParent();
		this->_target = nullptr;
	}
}

//------------------------------------------------------------------------------
// MARK: - Shake
//------------------------------------------------------------------------------

cocos2d::Sequence *Shake::create( float duration, float strength )
{

	auto halfDuration     = duration / 2;
	auto rotationDuration = halfDuration / 7;

	return cocos2d::Sequence::create(
	cocos2d::RotateBy::create( rotationDuration, strength ),
	cocos2d::RotateBy::create( rotationDuration, -2 * strength ),
	cocos2d::RotateBy::create( rotationDuration, strength * 1.7 ),
	cocos2d::RotateBy::create( rotationDuration, -1.2 * strength ),
	cocos2d::RotateBy::create( rotationDuration, 0.8 * strength ),
	cocos2d::RotateBy::create( rotationDuration, -0.4 * strength ),
	cocos2d::RotateBy::create( rotationDuration, 0.1 * strength ),
	cocos2d::DelayTime::create( halfDuration ), nullptr );
}

//------------------------------------------------------------------------------
// MARK: - LinealShake
//------------------------------------------------------------------------------

cocos2d::Sequence *
LinealShake::create( float duration, float x_strength, float y_strength, float z_strength )
{

	auto halfDuration     = duration / 2;
	auto movementDuration = halfDuration / 7;
	cocos2d::Vec3 strength( x_strength, y_strength, z_strength );

	return cocos2d::Sequence::create(
	cocos2d::MoveBy::create( movementDuration, strength ),
	cocos2d::MoveBy::create( movementDuration, -2 * strength ),
	cocos2d::MoveBy::create( movementDuration, strength * 1.7 ),
	cocos2d::MoveBy::create( movementDuration, -1.2 * strength ),
	cocos2d::MoveBy::create( movementDuration, 0.8 * strength ),
	cocos2d::MoveBy::create( movementDuration, -0.4 * strength ),
	cocos2d::MoveBy::create( movementDuration, 0.1 * strength ),
	cocos2d::DelayTime::create( halfDuration ), nullptr );
}

//------------------------------------------------------------------------------
// MARK: - MoveToNode
//------------------------------------------------------------------------------

MoveToNode::MoveToNode()
{
}

MoveToNode::~MoveToNode()
{
}

MoveToNode *MoveToNode::create( float duration, cocos2d::Node *destinationNode )
{
	MoveToNode *action = new ( std::nothrow ) MoveToNode();
	action->initWithDuration( duration, destinationNode );
	action->autorelease();
	return action;
}

bool MoveToNode::initWithDuration( float duration, cocos2d::Node *destination )
{
	if ( cocos2d::ActionInterval::initWithDuration( duration ) ) {
		this->destinationNode = destination;
	}
	return false;
}

MoveToNode *MoveToNode::clone() const
{
	auto a = new ( std::nothrow ) MoveToNode();
	a->initWithDuration( this->_duration, this->destinationNode );
	a->autorelease();
	return a;
}

MoveToNode *MoveToNode::reverse() const
{
	CCASSERT( false, "reverse() not supported in MoveToNode" );
	return nullptr;
}

void MoveToNode::startWithTarget( cocos2d::Node *target )
{
	cocos2d::ActionInterval::startWithTarget( target );

	this->originalPosition = this->_target->getPosition();

	for ( cocos2d::Node *parent = this->_target->getParent(); parent != nullptr;
	      parent                = parent->getParent() ) {
		this->originalPosition = parent->convertToWorldSpace( this->originalPosition );
	}
}

void MoveToNode::update( float time )
{
	cocos2d::Point finalPosition = this->destinationNode->getPosition();

	for ( cocos2d::Node *parent     = this->destinationNode->getParent();
	      parent != nullptr; parent = parent->getParent() ) {
		finalPosition = parent->convertToWorldSpace( finalPosition );
	}

	cocos2d::Vec2 delta = finalPosition - this->originalPosition;

	this->_target->setPosition( this->originalPosition + delta * time );
}

}; // namespace Actions
}; // namespace MK
