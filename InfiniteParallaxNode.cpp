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

constexpr const char *updateLayerCallbackFormat = "update_layer_%d";

void Self::addLayer( cocos2d::Sprite *node, int localZOrder, cocos2d::Vec2 velocity )
{
	char *callbackName = new char[100];
	std::sprintf( callbackName, updateLayerCallbackFormat, localZOrder );

	for ( auto child : this->getChildren() ) {
		if ( child->getLocalZOrder() == localZOrder ) {
			this->unschedule( callbackName );
			child->removeFromParent();
		}
	}

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

	std::function<void( float )> callback = [&, leftNode, rightNode, node, velocity,
	                                         CALLBACK_CALL_PERIOD]( float dt ) {

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
					right->setPosition( cocos2d::Point( left->getPosition().x -
					                                    right->getContentSize().width,
					                                    right->getPosition().y ) );
				}
			}
		}

		leftNode->runAction( cocos2d::MoveBy::create( CALLBACK_CALL_PERIOD, distances ) );
		rightNode->runAction( cocos2d::MoveBy::create( CALLBACK_CALL_PERIOD, distances ) );
		node->runAction( cocos2d::MoveBy::create( CALLBACK_CALL_PERIOD, distances ) );

	};

	this->schedule( callback, CALLBACK_CALL_PERIOD, callbackName );
	callback( 0 );

	delete[] callbackName;
}

}; // namespace MK
