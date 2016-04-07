//
//  FiniteTimeActions.hpp
//  Maw Kit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 21/02/16.
//
//

#ifndef FiniteTimeActions_hpp
#define FiniteTimeActions_hpp

#include "cocos2d.h"

namespace MK {

/**
 *  `Actions` namespace offers useful extra `FiniteTimeActions`.
 */
namespace Actions {

/// `RemoveFromParent` action removes a node from its parent after certain
/// delay.
class RemoveFromParent : public cocos2d::ActionInterval {
	public:
	/**
	 *  Creates an action that will remove a node from its parent after certain
	 *  delay.
	 *
	 *  @param duration Seconds to wait before removing node from parent.
	 *
	 *  @return An autoreleased `RemoveFromParent` object.
	 */
	static RemoveFromParent *create( float duration );

	//
	// Overrides
	//
	virtual RemoveFromParent *clone() const override;
	virtual RemoveFromParent *reverse( void ) const override;
	virtual void startWithTarget( cocos2d::Node *target ) override;
	virtual void update( float time ) override;

	CC_CONSTRUCTOR_ACCESS : RemoveFromParent();
	virtual ~RemoveFromParent();

	/**
	 *  Initializes the action with given duration.
	 *
	 *  @param duration Duration in seconds
	 *
	 *  @return Whether this instance could be initialized properly or not.
	 */
	bool initWithDuration( float duration );

	private:
	CC_DISALLOW_COPY_AND_ASSIGN( RemoveFromParent );
};

/// `Shake` action shakes a node during a certain delay.
class Shake : public cocos2d::Sequence {
	public:
	/**
	 *  Creates a shake action with given duration and strength (maximum
	 *  movement allowed).
	 *
	 *  @param duration Duration in seconds of the animation.
	 *  @param strength Maximum angle node will be rotated.
	 *
	 *  @return An autoreleased `Shake` object.
	 */
	static cocos2d::Sequence *create( float duration, float strength = 10 );

	private:
	CC_DISALLOW_COPY_AND_ASSIGN( Shake );
};

/// `LinealShake` action shakes a node during a certain delay in one axis.
class LinealShake : public cocos2d::Sequence {
	public:
	/**
	 *  Creates a lineal shake action with given duration and strength
	 *  (maximum movement allowed in given axis).
	 *
	 *  @param duration   Duration in seconds of the animation.
	 *  @param x_strength Maximum distance node will be moved in X axis.
	 *  @param y_strength Maximum distance node will be moved in Y axis.
	 *  @param z_strength Maximum distance node will be moved in Z axis.
	 *
	 *  @return An autoreleased `LinealShake` object.
	 */
	static cocos2d::Sequence *
	create( float duration, float x_strength = 0, float y_strength = 0, float z_strength = 0 );

	private:
	CC_DISALLOW_COPY_AND_ASSIGN( LinealShake );
};

/// `MoveToNode` action moves a node from its original location to the
/// location of given node, supporting moving to a node in movement.
class MoveToNode : public cocos2d::ActionInterval {
	public:
	/**
	 *  Creates an action that will move a node to the position of given
	 *  node.
	 *
	 *  @param duration        Duration of the animation.
	 *  @param destinationNode Destination node.
	 *
	 *  @return An autoreleased `MoveToNode` object.
	 */
	static MoveToNode *create( float duration, cocos2d::Node *destinationNode );

	//
	// Overrides
	//
	virtual MoveToNode *clone() const override;
	virtual MoveToNode *reverse( void ) const override;
	virtual void startWithTarget( cocos2d::Node *target ) override;
	virtual void update( float time ) override;

	CC_CONSTRUCTOR_ACCESS : MoveToNode();
	virtual ~MoveToNode();

	/**
	 *  Initializes the action with given duration.
	 *
	 *  @param duration        Duration of the animation.
	 *  @param destinationNode Destination node.
	 *
	 *  @return Whether this instance could be initialized properly or not.
	 */
	bool initWithDuration( float duration, cocos2d::Node *destinationNode );

	protected:
	/**
	 *  Node to be reached at the end of the animation.
	 */
	cocos2d::Node *destinationNode;

	/**
	 *  Original position of node to move.
	 */
	cocos2d::Point originalPosition;

	private:
	CC_DISALLOW_COPY_AND_ASSIGN( MoveToNode );
};

}; // namespace Actions
}; // namespace MK

#endif /* FiniteTimeActions_hpp */
