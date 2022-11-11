#ifndef __RXML_SCHEMA__
#define __RXML_SCHEMA__

#include <libxml/schemasInternals.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemastypes.h>

extern VALUE cXMLSchema;

void rxml_init_schema(void);

#define QNIL_OR_STRING(slot)			\
    if (slot == NULL) \
      return Qnil; \
    else \
	    return rb_str_new2((const char *)slot);

#define SUBSET_RESTRICTION  1<<0
#define SUBSET_EXTENSION    1<<1
#define SUBSET_SUBSTITUTION 1<<2
#define SUBSET_LIST         1<<3
#define SUBSET_UNION        1<<4

typedef struct _xmlSchemaNodeInfo xmlSchemaNodeInfo;
typedef xmlSchemaNodeInfo *xmlSchemaNodeInfoPtr;

typedef struct _xmlSchemaItemList xmlSchemaItemList;
typedef xmlSchemaItemList *xmlSchemaItemListPtr;
struct _xmlSchemaItemList {
    void **items;
    /* used for dynamic addition of schemata */
    int nbItems;
    /* used for dynamic addition of schemata */
    int sizeItems; /* used for dynamic addition of schemata */
};

#define XML_SCHEMA_CTXT_PARSER 1
#define XML_SCHEMA_CTXT_VALIDATOR 2

typedef struct _xmlSchemaAbstractCtxt xmlSchemaAbstractCtxt;
typedef xmlSchemaAbstractCtxt *xmlSchemaAbstractCtxtPtr;
struct _xmlSchemaAbstractCtxt {
    int type; /* E.g. XML_SCHEMA_CTXT_VALIDATOR */
};

typedef struct _xmlSchemaBucket xmlSchemaBucket;
typedef xmlSchemaBucket *xmlSchemaBucketPtr;

#define XML_SCHEMA_SCHEMA_MAIN 0
#define XML_SCHEMA_SCHEMA_IMPORT 1
#define XML_SCHEMA_SCHEMA_INCLUDE 2
#define XML_SCHEMA_SCHEMA_REDEFINE 3

/**
 * xmlSchemaSchemaRelation:
 *
 * Used to create a graph of schema relationships.
 */
typedef struct _xmlSchemaSchemaRelation xmlSchemaSchemaRelation;
typedef xmlSchemaSchemaRelation *xmlSchemaSchemaRelationPtr;
struct _xmlSchemaSchemaRelation {
    xmlSchemaSchemaRelationPtr next;
    int type;
    /* E.g. XML_SCHEMA_SCHEMA_IMPORT */
    const xmlChar *importNamespace;
    xmlSchemaBucketPtr bucket;
};

#define XML_SCHEMA_BUCKET_MARKED 1<<0
#define XML_SCHEMA_BUCKET_COMPS_ADDED 1<<1

struct _xmlSchemaBucket {
    int type;
    int flags;
    const xmlChar *schemaLocation;
    const xmlChar *origTargetNamespace;
    const xmlChar *targetNamespace;
    xmlDocPtr doc;
    xmlSchemaSchemaRelationPtr relations;
    int located;
    int parsed;
    int imported;
    int preserveDoc;
    xmlSchemaItemListPtr globals;
    /* Global components. */
    xmlSchemaItemListPtr locals; /* Local components. */
};

/**
 * xmlSchemaImport:
 * (extends xmlSchemaBucket)
 *
 * Reflects a schema. Holds some information
 * about the schema and its toplevel components. Duplicate
 * toplevel components are not checked at this level.
 */
typedef struct _xmlSchemaImport xmlSchemaImport;
typedef xmlSchemaImport *xmlSchemaImportPtr;
struct _xmlSchemaImport {
    int type;
    /* Main OR import OR include. */
    int flags;
    const xmlChar *schemaLocation; /* The URI of the schema document. */
    /* For chameleon includes, @origTargetNamespace will be NULL */
    const xmlChar *origTargetNamespace;
    /*
    * For chameleon includes, @targetNamespace will be the
    * targetNamespace of the including schema.
    */
    const xmlChar *targetNamespace;
    xmlDocPtr doc; /* The schema node-tree. */
    /* @relations will hold any included/imported/redefined schemas. */
    xmlSchemaSchemaRelationPtr relations;
    int located;
    int parsed;
    int imported;
    int preserveDoc;
    xmlSchemaItemListPtr globals;
    xmlSchemaItemListPtr locals;
    /* The imported schema. */
    xmlSchemaPtr schema;
};

/*
* (extends xmlSchemaBucket)
*/
typedef struct _xmlSchemaInclude xmlSchemaInclude;
typedef xmlSchemaInclude *xmlSchemaIncludePtr;
struct _xmlSchemaInclude {
    int type;
    int flags;
    const xmlChar *schemaLocation;
    const xmlChar *origTargetNamespace;
    const xmlChar *targetNamespace;
    xmlDocPtr doc;
    xmlSchemaSchemaRelationPtr relations;
    int located;
    int parsed;
    int imported;
    int preserveDoc;
    xmlSchemaItemListPtr globals;
    /* Global components. */
    xmlSchemaItemListPtr locals; /* Local components. */

    /* The owning main or import schema bucket. */
    xmlSchemaImportPtr ownerImport;
};

/**
 * xmlSchemaBasicItem:
 *
 * The abstract base type for schema components.
 */
typedef struct _xmlSchemaBasicItem xmlSchemaBasicItem;
typedef xmlSchemaBasicItem *xmlSchemaBasicItemPtr;
struct _xmlSchemaBasicItem {
    xmlSchemaTypeType type;
};

/**
 * xmlSchemaAnnotItem:
 *
 * The abstract base type for annotated schema components.
 * (Extends xmlSchemaBasicItem)
 */
typedef struct _xmlSchemaAnnotItem xmlSchemaAnnotItem;
typedef xmlSchemaAnnotItem *xmlSchemaAnnotItemPtr;
struct _xmlSchemaAnnotItem {
    xmlSchemaTypeType type;
    xmlSchemaAnnotPtr annot;
};

/**
 * xmlSchemaTreeItem:
 *
 * The abstract base type for tree-like structured schema components.
 * (Extends xmlSchemaAnnotItem)
 */
typedef struct _xmlSchemaTreeItem xmlSchemaTreeItem;
typedef xmlSchemaTreeItem *xmlSchemaTreeItemPtr;
struct _xmlSchemaTreeItem {
    xmlSchemaTypeType type;
    xmlSchemaAnnotPtr annot;
    xmlSchemaTreeItemPtr next;
    xmlSchemaTreeItemPtr children;
};


#define XML_SCHEMA_ATTR_USE_FIXED 1<<0
/**
 * xmlSchemaAttributeUsePtr:
 *
 * The abstract base type for tree-like structured schema components.
 * (Extends xmlSchemaTreeItem)
 */
typedef struct _xmlSchemaAttributeUse xmlSchemaAttributeUse;
typedef xmlSchemaAttributeUse *xmlSchemaAttributeUsePtr;
struct _xmlSchemaAttributeUse {
    xmlSchemaTypeType type;
    xmlSchemaAnnotPtr annot;
    xmlSchemaAttributeUsePtr next; /* The next attr. use. */
    /*
    * The attr. decl. OR a QName-ref. to an attr. decl. OR
    * a QName-ref. to an attribute group definition.
    */
    xmlSchemaAttributePtr attrDecl;

    int flags;
    xmlNodePtr node;
    int occurs;
    /* required, optional */
    const xmlChar *defValue;
    xmlSchemaValPtr defVal;
};

/**
 * xmlSchemaAttributeUseProhibPtr:
 *
 * A helper component to reflect attribute prohibitions.
 * (Extends xmlSchemaBasicItem)
 */
typedef struct _xmlSchemaAttributeUseProhib xmlSchemaAttributeUseProhib;
typedef xmlSchemaAttributeUseProhib *xmlSchemaAttributeUseProhibPtr;
struct _xmlSchemaAttributeUseProhib {
    xmlSchemaTypeType type;
    /* == XML_SCHEMA_EXTRA_ATTR_USE_PROHIB */
    xmlNodePtr node;
    const xmlChar *name;
    const xmlChar *targetNamespace;
    int isRef;
};

/**
 * xmlSchemaRedef:
 */
typedef struct _xmlSchemaRedef xmlSchemaRedef;
typedef xmlSchemaRedef *xmlSchemaRedefPtr;
struct _xmlSchemaRedef {
    xmlSchemaRedefPtr next;
    xmlSchemaBasicItemPtr item;
    /* The redefining component. */
    xmlSchemaBasicItemPtr reference;
    /* The referencing component. */
    xmlSchemaBasicItemPtr target;
    /* The to-be-redefined component. */
    const xmlChar *refName;
    /* The name of the to-be-redefined component. */
    const xmlChar *refTargetNs;
    /* The target namespace of the
  to-be-redefined comp. */
    xmlSchemaBucketPtr targetBucket; /* The redefined schema. */
};

/**
 * xmlSchemaConstructionCtxt:
 */
typedef struct _xmlSchemaConstructionCtxt xmlSchemaConstructionCtxt;
typedef xmlSchemaConstructionCtxt *xmlSchemaConstructionCtxtPtr;
struct _xmlSchemaConstructionCtxt {
    xmlSchemaPtr mainSchema;
    /* The main schema. */
    xmlSchemaBucketPtr mainBucket;
    /* The main schema bucket */
    xmlDictPtr dict;
    xmlSchemaItemListPtr buckets; /* List of schema buckets. */
    /* xmlSchemaItemListPtr relations; */ /* List of schema relations. */
xmlSchemaBucketPtr bucket;
    /* The current schema bucket */
    xmlSchemaItemListPtr pending;
    /* All Components of all schemas that
need to be fixed. */
    xmlHashTablePtr substGroups;
    xmlSchemaRedefPtr redefs;
    xmlSchemaRedefPtr lastRedef;
};

#define XML_SCHEMAS_PARSE_ERROR        1
#define SCHEMAS_PARSE_OPTIONS XML_PARSE_NOENT

struct _xmlSchemaParserCtxt {
    int type;
    void *errCtxt;
    /* user specific error context */
    xmlSchemaValidityErrorFunc error;
    /* the callback in case of errors */
    xmlSchemaValidityWarningFunc warning;
    /* the callback in case of warning */
    int err;
    int nberrors;
    xmlStructuredErrorFunc serror;

    xmlSchemaConstructionCtxtPtr constructor;
    int ownsConstructor; /* TODO: Move this to parser *flags*. */

    /* xmlSchemaPtr topschema;	*/
    /* xmlHashTablePtr namespaces;  */

    xmlSchemaPtr schema;
    /* The main schema in use */
    int counter;

    const xmlChar *URL;
    xmlDocPtr doc;
    int preserve;
    /* Whether the doc should be freed  */

    const char *buffer;
    int size;

    /*
     * Used to build complex element content models
     */
    xmlAutomataPtr am;
    xmlAutomataStatePtr start;
    xmlAutomataStatePtr end;
    xmlAutomataStatePtr state;

    xmlDictPtr dict;
    /* dictionnary for interned string names */
    xmlSchemaTypePtr ctxtType;
    /* The current context simple/complex type */
    int options;
    xmlSchemaValidCtxtPtr vctxt;
    int isS4S;
    int isRedefine;
    int xsiAssemble;
    int stop;
    /* If the parser should stop; i.e. a critical error. */
    const xmlChar *targetNamespace;
    xmlSchemaBucketPtr redefined;
    /* The schema to be redefined. */

    xmlSchemaRedefPtr redef;
    /* Used for redefinitions. */
    int redefCounter;
    /* Used for redefinitions. */
    xmlSchemaItemListPtr attrProhibs;
};

/**
 * xmlSchemaQNameRef:
 *
 * A component reference item (not a schema component)
 * (Extends xmlSchemaBasicItem)
 */
typedef struct _xmlSchemaQNameRef xmlSchemaQNameRef;
typedef xmlSchemaQNameRef *xmlSchemaQNameRefPtr;
struct _xmlSchemaQNameRef {
    xmlSchemaTypeType type;
    xmlSchemaBasicItemPtr item;
    /* The resolved referenced item. */
    xmlSchemaTypeType itemType;
    const xmlChar *name;
    const xmlChar *targetNamespace;
    xmlNodePtr node;
};

/**
 * xmlSchemaParticle:
 *
 * A particle component.
 * (Extends xmlSchemaTreeItem)
 */
typedef struct _xmlSchemaParticle xmlSchemaParticle;
typedef xmlSchemaParticle *xmlSchemaParticlePtr;
struct _xmlSchemaParticle {
    xmlSchemaTypeType type;
    xmlSchemaAnnotPtr annot;
    xmlSchemaTreeItemPtr next;
    /* next particle */
    xmlSchemaTreeItemPtr children;
    /* the "term" (e.g. a model group,
a group definition, a XML_SCHEMA_EXTRA_QNAMEREF (if a reference),
   etc.) */
    int minOccurs;
    int maxOccurs;
    xmlNodePtr node;
};

/**
 * xmlSchemaModelGroup:
 *
 * A model group component.
 * (Extends xmlSchemaTreeItem)
 */
typedef struct _xmlSchemaModelGroup xmlSchemaModelGroup;
typedef xmlSchemaModelGroup *xmlSchemaModelGroupPtr;
struct _xmlSchemaModelGroup {
    xmlSchemaTypeType type;
    /* XML_SCHEMA_TYPE_SEQUENCE, XML_SCHEMA_TYPE_CHOICE, XML_SCHEMA_TYPE_ALL */
    xmlSchemaAnnotPtr annot;
    xmlSchemaTreeItemPtr next;
    /* not used */
    xmlSchemaTreeItemPtr children;
    /* first particle (OR "element decl" OR "wildcard") */
    xmlNodePtr node;
};

#define XML_SCHEMA_MODEL_GROUP_DEF_MARKED 1<<0
#define XML_SCHEMA_MODEL_GROUP_DEF_REDEFINED 1<<1
/**
 * xmlSchemaModelGroupDef:
 *
 * A model group definition component.
 * (Extends xmlSchemaTreeItem)
 */
typedef struct _xmlSchemaModelGroupDef xmlSchemaModelGroupDef;
typedef xmlSchemaModelGroupDef *xmlSchemaModelGroupDefPtr;
struct _xmlSchemaModelGroupDef {
    xmlSchemaTypeType type;
    /* XML_SCHEMA_TYPE_GROUP */
    xmlSchemaAnnotPtr annot;
    xmlSchemaTreeItemPtr next;
    /* not used */
    xmlSchemaTreeItemPtr children;
    /* the "model group" */
    const xmlChar *name;
    const xmlChar *targetNamespace;
    xmlNodePtr node;
    int flags;
};

typedef struct _xmlSchemaIDC xmlSchemaIDC;
typedef xmlSchemaIDC *xmlSchemaIDCPtr;

/**
 * xmlSchemaIDCSelect:
 *
 * The identity-constraint "field" and "selector" item, holding the
 * XPath expression.
 */
typedef struct _xmlSchemaIDCSelect xmlSchemaIDCSelect;
typedef xmlSchemaIDCSelect *xmlSchemaIDCSelectPtr;
struct _xmlSchemaIDCSelect {
    xmlSchemaIDCSelectPtr next;
    xmlSchemaIDCPtr idc;
    int index;
    /* an index position if significant for IDC key-sequences */
    const xmlChar *xpath;
    /* the XPath expression */
    void *xpathComp; /* the compiled XPath expression */
};

/**
 * xmlSchemaIDC:
 *
 * The identity-constraint definition component.
 * (Extends xmlSchemaAnnotItem)
 */

struct _xmlSchemaIDC {
    xmlSchemaTypeType type;
    xmlSchemaAnnotPtr annot;
    xmlSchemaIDCPtr next;
    xmlNodePtr node;
    const xmlChar *name;
    const xmlChar *targetNamespace;
    xmlSchemaIDCSelectPtr selector;
    xmlSchemaIDCSelectPtr fields;
    int nbFields;
    xmlSchemaQNameRefPtr ref;
};

/**
 * xmlSchemaIDCAug:
 *
 * The augmented IDC information used for validation.
 */
typedef struct _xmlSchemaIDCAug xmlSchemaIDCAug;
typedef xmlSchemaIDCAug *xmlSchemaIDCAugPtr;
struct _xmlSchemaIDCAug {
    xmlSchemaIDCAugPtr next;
    /* next in a list */
    xmlSchemaIDCPtr def;
    /* the IDC definition */
    int keyrefDepth; /* the lowest tree level to which IDC
                        tables need to be bubbled upwards */
};

/**
 * xmlSchemaPSVIIDCKeySequence:
 *
 * The key sequence of a node table item.
 */
typedef struct _xmlSchemaPSVIIDCKey xmlSchemaPSVIIDCKey;
typedef xmlSchemaPSVIIDCKey *xmlSchemaPSVIIDCKeyPtr;
struct _xmlSchemaPSVIIDCKey {
    xmlSchemaTypePtr type;
    xmlSchemaValPtr val;
};

/**
 * xmlSchemaPSVIIDCNode:
 *
 * The node table item of a node table.
 */
typedef struct _xmlSchemaPSVIIDCNode xmlSchemaPSVIIDCNode;
typedef xmlSchemaPSVIIDCNode *xmlSchemaPSVIIDCNodePtr;
struct _xmlSchemaPSVIIDCNode {
    xmlNodePtr node;
    xmlSchemaPSVIIDCKeyPtr *keys;
    int nodeLine;
    int nodeQNameID;

};

/**
 * xmlSchemaPSVIIDCBinding:
 *
 * The identity-constraint binding item of the [identity-constraint table].
 */
typedef struct _xmlSchemaPSVIIDCBinding xmlSchemaPSVIIDCBinding;
typedef xmlSchemaPSVIIDCBinding *xmlSchemaPSVIIDCBindingPtr;
struct _xmlSchemaPSVIIDCBinding {
    xmlSchemaPSVIIDCBindingPtr next;
    /* next binding of a specific node */
    xmlSchemaIDCPtr definition;
    /* the IDC definition */
    xmlSchemaPSVIIDCNodePtr *nodeTable;
    /* array of key-sequences */
    int nbNodes;
    /* number of entries in the node table */
    int sizeNodes;
    /* size of the node table */
    xmlSchemaItemListPtr dupls;
};


#define XPATH_STATE_OBJ_TYPE_IDC_SELECTOR 1
#define XPATH_STATE_OBJ_TYPE_IDC_FIELD 2

#define XPATH_STATE_OBJ_MATCHES -2
#define XPATH_STATE_OBJ_BLOCKED -3

typedef struct _xmlSchemaIDCMatcher xmlSchemaIDCMatcher;
typedef xmlSchemaIDCMatcher *xmlSchemaIDCMatcherPtr;

/**
 * xmlSchemaIDCStateObj:
 *
 * The state object used to evaluate XPath expressions.
 */
typedef struct _xmlSchemaIDCStateObj xmlSchemaIDCStateObj;
typedef xmlSchemaIDCStateObj *xmlSchemaIDCStateObjPtr;
struct _xmlSchemaIDCStateObj {
    int type;
    xmlSchemaIDCStateObjPtr next;
    /* next if in a list */
    int depth;
    /* depth of creation */
    int *history;
    /* list of (depth, state-id) tuples */
    int nbHistory;
    int sizeHistory;
    xmlSchemaIDCMatcherPtr matcher;
    /* the correspondent field/selector
   matcher */
    xmlSchemaIDCSelectPtr sel;
    void *xpathCtxt;
};

#define IDC_MATCHER 0

/**
 * xmlSchemaIDCMatcher:
 *
 * Used to evaluate IDC selectors (and fields).
 */
struct _xmlSchemaIDCMatcher {
    int type;
    int depth;
    /* the tree depth at creation time */
    xmlSchemaIDCMatcherPtr next;
    /* next in the list */
    xmlSchemaIDCMatcherPtr nextCached;
    /* next in the cache list */
    xmlSchemaIDCAugPtr aidc;
    /* the augmented IDC item */
    int idcType;
    xmlSchemaPSVIIDCKeyPtr **keySeqs;
    /* the key-sequences of the target
   elements */
    int sizeKeySeqs;
    xmlSchemaItemListPtr targets; /* list of target-node
                                     (xmlSchemaPSVIIDCNodePtr) entries */
};

/*
* Element info flags.
*/
#define XML_SCHEMA_NODE_INFO_FLAG_OWNED_NAMES  1<<0
#define XML_SCHEMA_NODE_INFO_FLAG_OWNED_VALUES 1<<1
#define XML_SCHEMA_ELEM_INFO_NILLED           1<<2
#define XML_SCHEMA_ELEM_INFO_LOCAL_TYPE           1<<3

#define XML_SCHEMA_NODE_INFO_VALUE_NEEDED      1<<4
#define XML_SCHEMA_ELEM_INFO_EMPTY             1<<5
#define XML_SCHEMA_ELEM_INFO_HAS_CONTENT       1<<6

#define XML_SCHEMA_ELEM_INFO_HAS_ELEM_CONTENT  1<<7
#define XML_SCHEMA_ELEM_INFO_ERR_BAD_CONTENT  1<<8
#define XML_SCHEMA_NODE_INFO_ERR_NOT_EXPECTED  1<<9
#define XML_SCHEMA_NODE_INFO_ERR_BAD_TYPE  1<<10

/**
 * xmlSchemaNodeInfo:
 *
 * Holds information of an element node.
 */
struct _xmlSchemaNodeInfo {
    int nodeType;
    xmlNodePtr node;
    int nodeLine;
    const xmlChar *localName;
    const xmlChar *nsName;
    const xmlChar *value;
    xmlSchemaValPtr val;
    /* the pre-computed value if any */
    xmlSchemaTypePtr typeDef;
    /* the complex/simple type definition if any */

    int flags;
    /* combination of node info flags */

    int valNeeded;
    int normVal;

    xmlSchemaElementPtr decl;
    /* the element/attribute declaration */
    int depth;
    xmlSchemaPSVIIDCBindingPtr idcTable;
    /* the table of PSVI IDC bindings
 for the scope element*/
    xmlSchemaIDCMatcherPtr idcMatchers;
    /* the IDC matchers for the scope
   element */
    xmlRegExecCtxtPtr regexCtxt;

    const xmlChar **nsBindings;
    /* Namespace bindings on this element */
    int nbNsBindings;
    int sizeNsBindings;

    int hasKeyrefs;
    int appliedXPath; /* Indicates that an XPath has been applied. */
};

#define XML_SCHEMAS_ATTR_UNKNOWN 1
#define XML_SCHEMAS_ATTR_ASSESSED 2
#define XML_SCHEMAS_ATTR_PROHIBITED 3
#define XML_SCHEMAS_ATTR_ERR_MISSING 4
#define XML_SCHEMAS_ATTR_INVALID_VALUE 5
#define XML_SCHEMAS_ATTR_ERR_NO_TYPE 6
#define XML_SCHEMAS_ATTR_ERR_FIXED_VALUE 7
#define XML_SCHEMAS_ATTR_DEFAULT 8
#define XML_SCHEMAS_ATTR_VALIDATE_VALUE 9
#define XML_SCHEMAS_ATTR_ERR_WILD_STRICT_NO_DECL 10
#define XML_SCHEMAS_ATTR_HAS_ATTR_USE 11
#define XML_SCHEMAS_ATTR_HAS_ATTR_DECL 12
#define XML_SCHEMAS_ATTR_WILD_SKIP 13
#define XML_SCHEMAS_ATTR_WILD_LAX_NO_DECL 14
#define XML_SCHEMAS_ATTR_ERR_WILD_DUPLICATE_ID 15
#define XML_SCHEMAS_ATTR_ERR_WILD_AND_USE_ID 16
#define XML_SCHEMAS_ATTR_META 17
/*
* @metaType values of xmlSchemaAttrInfo.
*/
#define XML_SCHEMA_ATTR_INFO_META_XSI_TYPE 1
#define XML_SCHEMA_ATTR_INFO_META_XSI_NIL 2
#define XML_SCHEMA_ATTR_INFO_META_XSI_SCHEMA_LOC 3
#define XML_SCHEMA_ATTR_INFO_META_XSI_NO_NS_SCHEMA_LOC 4
#define XML_SCHEMA_ATTR_INFO_META_XMLNS 5

typedef struct _xmlSchemaAttrInfo xmlSchemaAttrInfo;
typedef xmlSchemaAttrInfo *xmlSchemaAttrInfoPtr;
struct _xmlSchemaAttrInfo {
    int nodeType;
    xmlNodePtr node;
    int nodeLine;
    const xmlChar *localName;
    const xmlChar *nsName;
    const xmlChar *value;
    xmlSchemaValPtr val;
    /* the pre-computed value if any */
    xmlSchemaTypePtr typeDef;
    /* the complex/simple type definition if any */
    int flags;
    /* combination of node info flags */

    xmlSchemaAttributePtr decl;
    /* the attribute declaration */
    xmlSchemaAttributeUsePtr use;
    /* the attribute use */
    int state;
    int metaType;
    const xmlChar *vcValue;
    /* the value constraint value */
    xmlSchemaNodeInfoPtr parent;
};


#define XML_SCHEMA_VALID_CTXT_FLAG_STREAM 1
/**
 * xmlSchemaValidCtxt:
 *
 * A Schemas validation context
 */
struct _xmlSchemaValidCtxt {
    int type;
    void *errCtxt;
    /* user specific data block */
    xmlSchemaValidityErrorFunc error;
    /* the callback in case of errors */
    xmlSchemaValidityWarningFunc warning;
    /* the callback in case of warning */
    xmlStructuredErrorFunc serror;

    xmlSchemaPtr schema;
    /* The schema in use */
    xmlDocPtr doc;
    xmlParserInputBufferPtr input;
    xmlCharEncoding enc;
    xmlSAXHandlerPtr sax;
    xmlParserCtxtPtr parserCtxt;
    void *user_data;
    /* TODO: What is this for? */

    int err;
    int nberrors;

    xmlNodePtr node;
    xmlNodePtr cur;
    /* xmlSchemaTypePtr type; */

    xmlRegExecCtxtPtr regexp;
    xmlSchemaValPtr value;

    int valueWS;
    int options;
    xmlNodePtr validationRoot;
    xmlSchemaParserCtxtPtr pctxt;
    int xsiAssemble;

    int depth;
    xmlSchemaNodeInfoPtr *elemInfos;
    /* array of element informations */
    int sizeElemInfos;
    xmlSchemaNodeInfoPtr inode;
    /* the current element information */

    xmlSchemaIDCAugPtr aidcs;
    /* a list of augmented IDC informations */

    xmlSchemaIDCStateObjPtr xpathStates;
    /* first active state object. */
    xmlSchemaIDCStateObjPtr xpathStatePool;
    /* first stored state object. */
    xmlSchemaIDCMatcherPtr idcMatcherCache;
    /* Cache for IDC matcher objects. */

    xmlSchemaPSVIIDCNodePtr *idcNodes;
    /* list of all IDC node-table entries*/
    int nbIdcNodes;
    int sizeIdcNodes;

    xmlSchemaPSVIIDCKeyPtr *idcKeys;
    /* list of all IDC node-table entries */
    int nbIdcKeys;
    int sizeIdcKeys;

    int flags;

    xmlDictPtr dict;

#ifdef LIBXML_READER_ENABLED
    xmlTextReaderPtr reader;
#endif

    xmlSchemaAttrInfoPtr *attrInfos;
    int nbAttrInfos;
    int sizeAttrInfos;

    int skipDepth;
    xmlSchemaItemListPtr nodeQNames;
    int hasKeyrefs;
    int createIDCNodeTables;
    int psviExposeIDCNodeTables;
};

/**
 * xmlSchemaSubstGroup:
 *
 *
 */
typedef struct _xmlSchemaSubstGroup xmlSchemaSubstGroup;
typedef xmlSchemaSubstGroup *xmlSchemaSubstGroupPtr;
struct _xmlSchemaSubstGroup {
    xmlSchemaElementPtr head;
    xmlSchemaItemListPtr members;
};

/*static xmlSchemaQNameRefPtr
        xmlSchemaParseAttributeGroupRef(xmlSchemaParserCtxtPtr pctxt,
        xmlSchemaPtr schema,
        xmlNodePtr node);*/


#endif

