//
//  CNContactRelation.h
//  Contacts
//
//  Copyright (c) 2015–2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract An immutable value object representing a related contact.
 *
 * @discussion CNContactRelation is thread safe.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNContactRelation : NSObject <NSCopying, NSSecureCoding>

+ (instancetype)contactRelationWithName:(NSString *)name;
- (instancetype)initWithName:(NSString *)name;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *name;

@end


// Contact relation labels
CONTACTS_EXTERN NSString * const CNLabelContactRelationAssistant                                                    NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationManager                                                      NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationColleague                                                    NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationTeacher                                                      NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationSibling                                                      NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerSibling                                               NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderSibling                                                 NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSister                                                       NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerSister                                                NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungestSister                                               NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderSister                                                  NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationEldestSister                                                 NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationBrother                                                      NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerBrother                                               NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungestBrother                                              NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderBrother                                                 NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationEldestBrother                                                NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationFriend                                                       NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationMaleFriend                                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationFemaleFriend                                                 NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationSpouse                                                       NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationWife                                                         NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationHusband                                                      NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationPartner                                                      NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationMalePartner                                                  NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationFemalePartner                                                NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGirlfriendOrBoyfriend                                        NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGirlfriend                                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationBoyfriend                                                    NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationParent                                                       NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationMother                                                       NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationFather                                                       NS_AVAILABLE(10_11, 9_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationChild                                                        NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationDaughter                                                     NS_AVAILABLE(10_13, 11_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSon                                                          NS_AVAILABLE(10_13, 11_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandparent                                                  NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandmother                                                  NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandmotherMothersMother                                     NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandmotherFathersMother                                     NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandfather                                                  NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandfatherMothersFather                                     NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandfatherFathersFather                                     NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationGreatGrandparent                                             NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGreatGrandmother                                             NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGreatGrandfather                                             NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandchild                                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGranddaughter                                                NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGranddaughterDaughtersDaughter                               NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGranddaughterSonsDaughter                                    NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandson                                                     NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandsonDaughtersSon                                         NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandsonSonsSon                                              NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationGreatGrandchild                                              NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGreatGranddaughter                                           NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGreatGrandson                                                NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationParentInLaw                                                  NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationMotherInLaw                                                  NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationMotherInLawWifesMother                                       NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationMotherInLawHusbandsMother                                    NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationFatherInLaw                                                  NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationFatherInLawWifesFather                                       NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationFatherInLawHusbandsFather                                    NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationCoParentInLaw                                                NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationCoMotherInLaw                                                NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationCoFatherInLaw                                                NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationSiblingInLaw                                                 NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerSiblingInLaw                                          NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderSiblingInLaw                                            NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationSisterInLaw                                                  NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerSisterInLaw                                           NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderSisterInLaw                                             NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSisterInLawSpousesSister                                     NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSisterInLawWifesSister                                       NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSisterInLawHusbandsSister                                    NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSisterInLawBrothersWife                                      NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSisterInLawYoungerBrothersWife                               NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSisterInLawElderBrothersWife                                 NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationBrotherInLaw                                                 NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerBrotherInLaw                                          NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderBrotherInLaw                                            NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationBrotherInLawSpousesBrother                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationBrotherInLawHusbandsBrother                                  NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationBrotherInLawWifesBrother                                     NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationBrotherInLawSistersHusband                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationBrotherInLawYoungerSistersHusband                            NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationBrotherInLawElderSistersHusband                              NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationSisterInLawWifesBrothersWife                                 NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSisterInLawHusbandsBrothersWife                              NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationBrotherInLawWifesSistersHusband                              NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationBrotherInLawHusbandsSistersHusband                           NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationCoSiblingInLaw                                               NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationCoSisterInLaw                                                NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationCoBrotherInLaw                                               NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationChildInLaw                                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationDaughterInLaw                                                NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSonInLaw                                                     NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationCousin                                                       NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerCousin                                                NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderCousin                                                  NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationMaleCousin                                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationFemaleCousin                                                 NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationCousinParentsSiblingsChild                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationCousinParentsSiblingsSon                                     NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerCousinParentsSiblingsSon                              NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderCousinParentsSiblingsSon                                NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationCousinParentsSiblingsDaughter                                NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerCousinParentsSiblingsDaughter                         NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderCousinParentsSiblingsDaughter                           NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationCousinMothersSistersDaughter                                 NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerCousinMothersSistersDaughter                          NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderCousinMothersSistersDaughter                            NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationCousinMothersSistersSon                                      NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerCousinMothersSistersSon                               NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderCousinMothersSistersSon                                 NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationCousinMothersBrothersDaughter                                NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerCousinMothersBrothersDaughter                         NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderCousinMothersBrothersDaughter                           NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationCousinMothersBrothersSon                                     NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerCousinMothersBrothersSon                              NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderCousinMothersBrothersSon                                NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationCousinFathersSistersDaughter                                 NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerCousinFathersSistersDaughter                          NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderCousinFathersSistersDaughter                            NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationCousinFathersSistersSon                                      NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerCousinFathersSistersSon                               NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderCousinFathersSistersSon                                 NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationCousinFathersBrothersDaughter                                NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerCousinFathersBrothersDaughter                         NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderCousinFathersBrothersDaughter                           NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationCousinFathersBrothersSon                                     NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerCousinFathersBrothersSon                              NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderCousinFathersBrothersSon                                NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationCousinGrandparentsSiblingsChild                              NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationCousinGrandparentsSiblingsDaughter                           NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationCousinGrandparentsSiblingsSon                                NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerCousinMothersSiblingsSonOrFathersSistersSon           NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderCousinMothersSiblingsSonOrFathersSistersSon             NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationYoungerCousinMothersSiblingsDaughterOrFathersSistersDaughter NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationElderCousinMothersSiblingsDaughterOrFathersSistersDaughter   NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationParentsSibling                                               NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationParentsYoungerSibling                                        NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationParentsElderSibling                                          NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationParentsSiblingMothersSibling                                 NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationParentsSiblingMothersYoungerSibling                          NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationParentsSiblingMothersElderSibling                            NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationParentsSiblingFathersSibling                                 NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationParentsSiblingFathersYoungerSibling                          NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationParentsSiblingFathersElderSibling                            NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationAunt                                                         NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationAuntParentsSister                                            NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationAuntParentsYoungerSister                                     NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationAuntParentsElderSister                                       NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationAuntFathersSister                                            NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationAuntFathersYoungerSister                                     NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationAuntFathersElderSister                                       NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationAuntFathersBrothersWife                                      NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationAuntFathersYoungerBrothersWife                               NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationAuntFathersElderBrothersWife                                 NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationAuntMothersSister                                            NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationAuntMothersYoungerSister                                     NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationAuntMothersElderSister                                       NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationAuntMothersBrothersWife                                      NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandaunt                                                    NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationUncle                                                        NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationUncleParentsBrother                                          NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationUncleParentsYoungerBrother                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationUncleParentsElderBrother                                     NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationUncleMothersBrother                                          NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationUncleMothersYoungerBrother                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationUncleMothersElderBrother                                     NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationUncleMothersSistersHusband                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationUncleFathersBrother                                          NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationUncleFathersYoungerBrother                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationUncleFathersElderBrother                                     NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationUncleFathersSistersHusband                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationUncleFathersYoungerSistersHusband                            NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationUncleFathersElderSistersHusband                              NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationGranduncle                                                   NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationSiblingsChild                                                NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationNiece                                                        NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationNieceSistersDaughter                                         NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationNieceBrothersDaughter                                        NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationNieceSistersDaughterOrWifesSiblingsDaughter                  NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationNieceBrothersDaughterOrHusbandsSiblingsDaughter              NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationNephew                                                       NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationNephewSistersSon                                             NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationNephewBrothersSon                                            NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationNephewBrothersSonOrHusbandsSiblingsSon                       NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationNephewSistersSonOrWifesSiblingsSon                           NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandniece                                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandnieceSistersGranddaughter                               NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandnieceBrothersGranddaughter                              NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandnephew                                                  NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandnephewSistersGrandson                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandnephewBrothersGrandson                                  NS_AVAILABLE(10_15, 13_0);

CONTACTS_EXTERN NSString * const CNLabelContactRelationStepparent                                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationStepmother                                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationStepfather                                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationStepchild                                                    NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationStepdaughter                                                 NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationStepson                                                      NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationStepsister                                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationStepbrother                                                  NS_AVAILABLE(10_15, 13_0);


// Additional international labels consisting of conjunctions of English terms:
CONTACTS_EXTERN NSString * const CNLabelContactRelationMotherInLawOrStepmother                                      NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationFatherInLawOrStepfather                                      NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationDaughterInLawOrStepdaughter                                  NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSonInLawOrStepson                                            NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationCousinOrSiblingsChild                                        NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationNieceOrCousin                                                NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationNephewOrCousin                                               NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandchildOrSiblingsChild                                    NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGranddaughterOrNiece                                         NS_AVAILABLE(11_0, 14_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGrandsonOrNephew                                             NS_AVAILABLE(11_0, 14_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationGreatGrandchildOrSiblingsGrandchild                          NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationDaughterInLawOrSisterInLaw                                   NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelContactRelationSonInLawOrBrotherInLaw                                       NS_AVAILABLE(10_15, 13_0);



NS_ASSUME_NONNULL_END
