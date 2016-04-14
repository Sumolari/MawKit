//
//  InfiniteParallaxNode.cpp
//  MawKit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 08/04/16.
//
//

#include "InfiniteParallaxNode.hpp"

namespace MK {

typedef InfiniteParallaxNode Self;

constexpr const char *updateLayerCallbackFormat = "update_layer_%d_%c_axis";

void Self::addLayer( cocos2d::Sprite *node, int localZOrder, cocos2d::Vec2 velocity )
{
	char *callbackNameXAxis = new char[100];
	std::sprintf( callbackNameXAxis, updateLayerCallbackFormat, localZOrder, 'x' );
	char *callbackNameYAxis = new char[100];
	std::sprintf( callbackNameYAxis, updateLayerCallbackFormat, localZOrder, 'y' );

	for ( auto child : this->getChildren() ) {
		if ( child->getLocalZOrder() == localZOrder ) {
			this->unschedule( callbackNameXAxis );
			this->unschedule( callbackNameYAxis );
			child->removeFromParent();
		}
	}

	if ( velocity.x != 0 ) {

		auto leftNode = cocos2d::Sprite::createWithTexture( node->getTexture() );
		leftNode->setAnchorPoint( node->getAnchorPoint() );
		leftNode->setContentSize( node->getContentSize() );
		leftNode->setPosition( node->getPosition() +
		                       cocos2d::Point( -node->getContentSize().width, 0 ) );

		auto rightNode = cocos2d::Sprite::createWithTexture( node->getTexture() );
		rightNode->setAnchorPoint( node->getAnchorPoint() );
		rightNode->setContentSize( node->getContentSize() );
		rightNode->setPosition( node->getPosition() +
		                        cocos2d::Point( node->getContentSize().width, 0 ) );

		this->addChild( node, localZOrder );
		this->addChild( leftNode, localZOrder );
		this->addChild( rightNode, localZOrder );

		constexpr const float CALLBACK_CALL_PERIOD = 1.0;

		std::function<void( float )> callback_x_axis =
		[&, leftNode, rightNode, node, velocity, CALLBACK_CALL_PERIOD]( float dt ) {

			auto distances = velocity * CALLBACK_CALL_PERIOD;

			if ( velocity.x < 0 ) {

				std::vector<std::pair<cocos2d::Node *, cocos2d::Node *>> nodes = {
				{leftNode, rightNode}, {node, leftNode}, {rightNode, node}};

				for ( auto pair : nodes ) {
					auto left  = pair.first;
					auto right = pair.second;
					if ( left->getPosition().x < -left->getContentSize().width * 1.5 ) {
						left->setPosition( cocos2d::Point( right->getPosition().x +
						                                   left->getContentSize().width,
						                                   left->getPosition().y ) );
					}
				}
			}
			else {

				std::vector<std::pair<cocos2d::Node *, cocos2d::Node *>> nodes = {
				{rightNode, leftNode}, {leftNode, node}, {node, rightNode}};

				for ( auto pair : nodes ) {
					auto right = pair.first;
					auto left  = pair.second;
					if ( right->getPosition().x > right->getContentSize().width * 1.5 ) {
						right->setPosition(
						cocos2d::Point( left->getPosition().x - right->getContentSize().width,
						                right->getPosition().y ) );
					}
				}
			}

			leftNode->runAction( cocos2d::MoveBy::create( CALLBACK_CALL_PERIOD, distances ) );
			rightNode->runAction( cocos2d::MoveBy::create( CALLBACK_CALL_PERIOD, distances ) );
			node->runAction( cocos2d::MoveBy::create( CALLBACK_CALL_PERIOD, distances ) );

		};

		this->schedule( callback_x_axis, CALLBACK_CALL_PERIOD, callbackNameXAxis );
		callback_x_axis( 0 );
	}

	if ( velocity.y != 0 ) {

		auto topNode = cocos2d::Sprite::createWithTexture( node->getTexture() );
		topNode->setAnchorPoint( node->getAnchorPoint() );
		topNode->setContentSize( node->getContentSize() );
		topNode->setPosition( node->getPosition() +
		                      cocos2d::Point( 0, -node->getContentSize().height ) );

		auto bottomNode = cocos2d::Sprite::createWithTexture( node->getTexture() );
		bottomNode->setAnchorPoint( node->getAnchorPoint() );
		bottomNode->setContentSize( node->getContentSize() );
		bottomNode->setPosition(
		node->getPosition() + cocos2d::Point( 0, node->getContentSize().height ) );

		this->addChild( node, localZOrder );
		this->addChild( topNode, localZOrder );
		this->addChild( bottomNode, localZOrder );

		constexpr const float CALLBACK_CALL_PERIOD = 1.0;

		std::function<void( float )> callback_y_axis =
		[&, topNode, bottomNode, node, velocity, CALLBACK_CALL_PERIOD]( float dt ) {

			auto distances = velocity * CALLBACK_CALL_PERIOD;

			if ( velocity.y < 0 ) {

				std::vector<std::pair<cocos2d::Node *, cocos2d::Node *>> nodes = {
				{topNode, bottomNode}, {node, topNode}, {bottomNode, node}};

				for ( auto pair : nodes ) {
					auto top    = pair.first;
					auto bottom = pair.second;
					if ( top->getPosition().y < -bottom->getContentSize().height * 1.5 ) {
						top->setPosition( cocos2d::Point( top->getPosition().x,
						                                  bottom->getPosition().y +
						                                  top->getContentSize().height ) );
					}
				}
			}
			else {

				std::vector<std::pair<cocos2d::Node *, cocos2d::Node *>> nodes = {
				{bottomNode, topNode}, {topNode, node}, {node, bottomNode}};

				for ( auto pair : nodes ) {
					auto bottom = pair.first;
					auto top    = pair.second;
					if ( bottom->getPosition().y > bottom->getContentSize().height * 1.5 ) {
						bottom->setPosition(
						cocos2d::Point( bottom->getPosition().x,
						                top->getPosition().y -
						                bottom->getContentSize().height ) );
					}
				}
			}

			topNode->runAction( cocos2d::MoveBy::create( CALLBACK_CALL_PERIOD, distances ) );
			bottomNode->runAction( cocos2d::MoveBy::create( CALLBACK_CALL_PERIOD, distances ) );
			node->runAction( cocos2d::MoveBy::create( CALLBACK_CALL_PERIOD, distances ) );

		};

		this->schedule( callback_y_axis, CALLBACK_CALL_PERIOD, callbackNameYAxis );
		callback_y_axis( 0 );
	}

	delete[] callbackNameXAxis;
	delete[] callbackNameYAxis;
}

}; // namespace MK
