//
//  GKRuleSystem.h
//  GameplayKit
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameplayKitBase.h"

NS_ASSUME_NONNULL_BEGIN

@class GKRule;

/**
 * A rule system consists of 3 things:
 * - The current state, which upon creation is considered the inital state.
 * - The current set of rules.
 * - The current set of facts.
 * 
 * Each time a fact is added to the system, the set of rules are evaluated in order and their actions executed in the system if their predicates are true.
 * Rules can be fuzzy, allowing predicates and facts to be asserted to a degree of confidence instead of just boolean on/off.
 * 
 * The facts can be any kind of objects as long as they correctly determine equality using isEqual:
 * The simplest approach is to use strings or dictionaries as they provide the most flexibility in defining
 * facts, but user defined classes work just as well and may describe the problem space better.
 *
 * The fact set is at all times a fuzzy set, as defined by fact membership in the set being modulated by their
 * grade of membership. The rules may use the grade of membership to predicate their actions and in such a
 * manner create fuzzy logic. The fuzzy logic Zadeh operators are available on the system itself in order
 * to query multiple facts for combined membership grade.
 */
GK_BASE_AVAILABILITY @interface GKRuleSystem : NSObject

/**
 * Initializes a clean rule system with no state, rules or facts.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 * Explicitly evaluate the agenda of the rule system based on the current state and the current set of facts.
 *
 * This may in turn assert or retract more facts or change the state of the system, including activating more
 * rules in the agenda.
 */
- (void)evaluate;

/**
 * The implementation-defined state. If any changes are made on this outside the system you must
 * call evaluate to have the system take account of the changes.
 *
 * @see evaluate
 */
@property (nonatomic, retain, readonly) NSMutableDictionary *state;

#pragma mark Rules
/**
 * The current set of rules that will be used to set the agenda when rules are first added to the system.
 * They will also be used to refill the agenda whenever it is set.
 *
 * This is at all times the union of the agenda and executed sets.
 *
 * @see agenda
 * @see executed
 */
@property (nonatomic, retain, readonly) NSArray<GKRule *> *rules;

/**
 * Adds a rule to the system. Also adds it to the agenda in salience order.
 */
- (void)addRule:(GKRule *)rule;

/**
 * Adds rules to the system. Also adds them to the agenda in salience order.
 */
- (void)addRulesFromArray:(NSArray<GKRule *> *)rules;

/**
 * Removes all rules from the system.  This also removes them from the agenda and executed sets.
 */
- (void)removeAllRules;

/**
 * The current set of rules to be evaluated, in salience order, where if the salience is equivalent
 * the order of insertion into the agenda is used to decide which is first.
 * Adjust salience of your rules to adjust the order the next time the agenda is reset. Changing salience
 * on a rule currently in the agenda does not change its order in the agenda.
 *
 * This is at all times the difference between the rules and executed sets.
 *
 * @see rules
 * @see executed
 * @see reset
 */
@property (nonatomic, retain, readonly) NSArray<GKRule *> *agenda;

/**
 * The current set of rules that have already executed. Rules in this set will not be executed again until
 * the system is reset.
 *
 * This is at all times the difference between the rules and agenda sets.
 *
 * @see rules
 * @see agenda
 * @see reset
 */
@property (nonatomic, retain, readonly) NSArray<GKRule *> *executed;

#pragma mark Facts

/**
 * The current set of facts. Facts have a grade of membership that is >= 0.0. Query the system for the
 * individual grades of membership with gradeForFact:
 *
 * @see gradeForFact:
 */
@property (nonatomic, retain, readonly) NSArray *facts;

#pragma mark Zadeh operators
/**
 * Returns the current membership grade for the given fact, which is 0.0 if the fact
 * is not a member of the current set of facts.
 *
 * @return The membership grade of the given fact, in the range [0.0, 1.0].
 */
- (float)gradeForFact:(id<NSObject>)fact;

/**
 * Returns the combined membership grade for the all the given facts.
 *
 * This performs the logical AND operation between the given facts.
 *
 * @return The membership grade by applying the AND operator on the given facts, in the range [0.0, 1.0].
 */
- (float)minimumGradeForFacts:(NSArray *)facts;

/**
 * Returns the maximum membership grade for the any one of the given facts.
 *
 * This performs the logical OR operation between the given facts.
 *
 * @return The membership grade by applying the OR operator on the given facts, in the range [0.0, 1.0].
 */
- (float)maximumGradeForFacts:(NSArray *)facts;

#pragma mark Asserting Facts
/**
 * Asserts a fact with membership grade of 1.0.
 *
 * This will cause the current rules to be evaluated, which may in turn assert or retract more facts
 * or change the state of the system.
 *
 * This is shorthand for calling assertFact:grade: with a grade of 1.0
 *
 * @see assertFact:grade:
 * @see evaluate
 * @see NSObject.isEqual:
 */
- (void)assertFact:(id<NSObject>)fact;

/**
 * Asserts a fact with the supplied membership grade.
 * 
 * This will cause the current rules to be evaluated, which may in turn assert or retract more facts
 * or change the state of the system.
 * 
 * @see evaluate
 */
- (void)assertFact:(id<NSObject>)fact grade:(float)grade;

#pragma mark Retracting Facts
/**
 * Retracts a fact, setting its membership grade to 0, which also removes it from the fact set.
 *
 * This will cause the current rules to be evaluated, which may in turn assert or retract more facts
 * or change the state of the system.
 *
 * This is short hand for calling retractFact:grade: with a grade of 1.0
 *
 * @see retractFact:grade:
 * @see evaluate
 */
- (void)retractFact:(id<NSObject>)fact;

/**
 * Retracts a fact, reducing its membership grade by the supplied grade. If this brings the grade to 0
 * it is also removed from the fact set.
 *
 * This will cause the current rules to be evaluated, which may in turn assert or retract more facts
 * or change the state of the system.
 *
 * @see evaluate
 */
- (void)retractFact:(id<NSObject>)fact grade:(float)grade;

#pragma mark Resetting the system

/**
 * Clears the agenda and executed sets and removes all facts currently in the system.
 * It then fills the agenda with rules from the rule set, in salience order.
 * @see rules
 * @see facts
 */
- (void)reset;

@end


/**
 * The concrete class that the GKRuleSystem uses to evaluate the current state and facts with predicated rules.
 * These are sharable between systems, so don't retain any state in the rules themselves. Use the system-provided
 * state storage.
 * 
 * @see GKRuleSystem.state
 */
GK_BASE_AVAILABILITY @interface GKRule : NSObject

/**
 * Salience defines the order in the rule agenda that the system will evaluate. A rule with higher salience will
 * be evaluated before another rule in the agenda that has a lower salience.
 *
 * Defaults to 0.
 * @see GKRuleSystem.agenda
 */
@property (nonatomic, assign) NSInteger salience;

/**
 * Called by the rule system when it is this rule's turn to be evaluated. If the predicate returns YES then
 * the action for the rule will be performed. Once the action is performed the rule will move to the system's
 * executed list until the agenda is reset.
 *
 * @see performAction
 * @see GKRuleSystem.agenda
 * @see GKRuleSystem.executed
 * @see GKRuleSystem.reset
 * @return YES is the predicate passes and the action needs to be performed, NO otherwise.
 */
- (BOOL)evaluatePredicateWithSystem:(GKRuleSystem *)system;

/**
 * Performs the action consequence for the rule. This will only be called if the predicate evaluates to YES.
 * Any facts asserted or retracted by the action on the system will cause the system to evaluate the agenda
 * rule set again once the action completes.
 */
- (void)performActionWithSystem:(GKRuleSystem *)system;

/**
 * Create a data-driven rule that uses NSPredicate and a single assert as the action.
 */
+ (instancetype)ruleWithPredicate:(NSPredicate *)predicate assertingFact:(id<NSObject>)fact grade:(float)grade;

/**
 * Short hand for data-driven rule that uses NSPredicate and a single retract as the action.
 */
+ (instancetype)ruleWithPredicate:(NSPredicate *)predicate retractingFact:(id<NSObject>)fact grade:(float)grade;

/**
 * Short hand for making a rule that uses blocks for the predicate and action. This rule is not able to be archived
 * using NSKeyedArchiver so use a subclass or NSPredicate based rule if serialization of the rule is needed.
 */
+ (instancetype)ruleWithBlockPredicate:(BOOL (^)(GKRuleSystem *))predicate action:(void (^)(GKRuleSystem *))action;

@end


/**
 * A convenient subclass of GKRule that leverages existing NSPRedicate functionality for evaluating the predicate
 * of the rule.
 */
GK_BASE_AVAILABILITY @interface GKNSPredicateRule : GKRule

/**
 * The NSPredicate that is used inside this subclass's implementation of evaluatePredicateWithSystem:
 * In order to effectively use this class you must still override performActionWithSystem:
 *
 * @see GKRule.evaluatePredicateWithSystem:
 */
@property (nonatomic, retain, readonly) NSPredicate *predicate;

/**
 * Initializes a new rule with the given NSPredicate
 */
- (instancetype)initWithPredicate:(NSPredicate *)predicate;

/**
 * Overridden here to call the predicate's evaluateWithObject:substitutionVariables:, using sys
 * as the object and the system's state dictionary as the source of the substitution variables.
 *
 * @return YES if the NSPredicate evaluation passes and the action needs to be performed, NO otherwise.
 */
- (BOOL)evaluatePredicateWithSystem:(GKRuleSystem *)system;

@end

NS_ASSUME_NONNULL_END

