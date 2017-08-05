//
//  GKDecisionTreeStrategist.h
//  GameplayKit
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <GameplayKit/GameplayKitBase.h>
#import <GameplayKit/GKRandomSource.h>

NS_ASSUME_NONNULL_BEGIN

GK_BASE_AVAILABILITY_2 @interface GKDecisionNode : NSObject

/**
 * Creates a numeric branch to a node containing the specified attribute
 *
 * @param branch The branch of this node for the specified value
 * @param attribute The attribute of the created node
 * @return The node lead to by the branch
 */
- (instancetype)createBranchWithValue:(NSNumber *)value attribute:(id <NSObject>)attribute;

/**
 * Creates a predicated branch to a node containing the specified attribute
 *
 * @param branch The branch of this node for the provided predicate
 * @param attribute The attribute of the created node
 * @return The node lead to by the branch
 */
- (instancetype)createBranchWithPredicate:(NSPredicate *)predicate attribute:(id <NSObject>)attribute;

/**
 * Creates a random branch to a node containing the specified attribute
 *
 * @param branch The branch of this node with the given weight (weighted for random selection)
 * @param attribute The attribute of the created node
 * @return The node lead to by the branch
 *
 * @see GKDecisionTree
 */
- (instancetype)createBranchWithWeight:(NSInteger)weight attribute:(id <NSObject>)attribute;

@end


GK_BASE_AVAILABILITY_2 @interface GKDecisionTree : NSObject <NSSecureCoding>

/**
 * The node for the decision tree that all other nodes descend from
 */
@property (nonatomic, readonly, nullable) GKDecisionNode *rootNode;

/**
 * The random source used by the decision tree when descending on a random branch
 * This must be set before creating any weighted branches
 * @see GKDecisionNode
 */
@property (copy, nonatomic) GKRandomSource *randomSource;

/**
 * Initializes the decision tree with a root node containing the provided attribute
 *
 * @param attribute The attribute to be contained at the root of the tree
 * @return GKDecisionTree with the set root
 */
- (instancetype)initWithAttribute:(id <NSObject>)attribute;

/**
 * Initializes and constructs a decision tree by learning from the provided examples & attributes
 *
 * @param examples Must be an array of examples (with each example being a collection of the various attributes at a given state)
 * @param results An array of the corresponding results for each example. Ordered such that the first result matches with the first example in examples.
 * @param attributes The list of attributes. Ordered such that the first attribute matches with the first result in each example.
 * So if we have two attributes: [distance, jump height], and two examples: [[20, 8], [15, 14]], and the resulting actions here: [Roll, Jump], we can think of this as a matrix:
 *
 *          distance| height            <-  Attributes
 *           _______|_______
 *          |       |       |
 *          |  20   |   8   |  jump
 *          |-------|-------|-------    <-  Results
 *          |  15   |   14  |  roll
 *          |_______|_______|
 *                  ^
 *                  |
 *               Examples
 *
 * @return GKDecisionTree created by learning from the provided examples for the provided attributes
 */
- (instancetype)initWithExamples:(NSArray <NSArray <id <NSObject>>*>*)examples actions:(NSArray <id <NSObject>>*)actions attributes:(NSArray <id <NSObject>>*)attributes;

/**
 * Will branch down from the root node to find the correct action attribute for the given collection of results and their respective attributes
 *
 * @param answers The dictionary of attributes (keys) and their answers (values)
 * @return The attribute found by traversing the tree given the provided answers
 */
- (nullable id <NSObject>)findActionForAnswers:(NSDictionary <id <NSObject>, id <NSObject>>*)answers;

@end

NS_ASSUME_NONNULL_END
