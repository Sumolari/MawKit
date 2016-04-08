//
//  InfiniteParallaxNode.hpp
//  MawKit
//
//  Created by Lluís Ulzurrun de Asanza Sàez on 08/04/16.
//
//

#ifndef InfiniteParallaxNode_hpp
#define InfiniteParallaxNode_hpp

#include "cocos2d.h"

namespace MK {

class InfiniteParallaxNode : public cocos2d::Node {
	public:
	CREATE_FUNC( InfiniteParallaxNode );

	/**
	 *  Adds given node to this parallax hierarchy.
	 *
	 *  @param node        Node to be add.
	 *  @param localZOrder ZPosition of node to be added.
	 *  @param velocity    Velocity of node to be added, in points per second.
	 */
	void addLayer( cocos2d::Sprite *node, int localZOrder, cocos2d::Vec2 velocity );
};

}; // namespace MK

#endif /* InfiniteParallaxNode_hpp */
