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
 * @param value The value to create a branch with
 * @param attribute The attribute of the created node
 * @return The node lead to by the branch
 */
- (instancetype)createBranchWithValue:(NSNumber *)value attribute:(id <NSObject>)attribute;

/**
 * Creates a predicated branch to a node containing the specified attribute
 *
 * @param predicate The predicate to create a branch with
 * @param attribute The attribute of the created node
 * @return The node lead to by the branch
 */
- (instancetype)createBranchWithPredicate:(NSPredicate *)predicate attribute:(id <NSObject>)attribute;

/**
 * Creates a random branch to a node containing the specified attribute
 *
 * @param weight The weight to create a branch with (weighted for random selection)
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
 * @param actions An array of the corresponding actions for each example. Ordered such that the first action matches with the first example in examples.
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
 * Initializes a decision tree from the contents of a file
 *
 * @param url The URL from which the contents will be loaded
 * @return The instance of the decision tree constructed
 */
- (instancetype)initWithURL:(NSURL *)url error:(NSError * _Nullable)error;

/**
 * Exports a decision tree to the given URL
 *
 * @param url The URL to which the contents will be exported
 * @return The response indicating the status of the decision tree being successfully exported
 */
- (BOOL)exportToURL:(NSURL *)url error:(NSError * _Nullable)error;

/**
 * Will branch down from the root node to find the correct action attribute for the given collection of results and their respective attributes
 *
 * @param answers The dictionary of attributes (keys) and their answers (values)
 * @return The attribute found by traversing the tree given the provided answers
 */
- (nullable id <NSObject>)findActionForAnswers:(NSDictionary <id <NSObject>, id <NSObject>>*)answers;

@end

NS_ASSUME_NONNULL_END
