# =XMPP4R - XMPP Library for Ruby
# License:: Ruby's license (see the LICENSE file) or GNU GPL, at your option.
# Website::http://home.gna.org/xmpp4r/
#
# ==Introduction
#
# XMPP4R is a XMPP/Jabber library for Ruby. It can be used to build scripts
# using Jabber, full-featured Jabber clients, and components. It is written
# with extensibility in mind.
#
# ==XML management
#
# All the XML parsing is REXML's, and XML stanzas like <message/> (class
# <tt>Jabber::Message</tt>) or <iq/> (class <tt>Jabber::Iq</tt>) are indirect
# derivatives from REXML's Element class. This provide a maximum flexibity:
# the user can access attributes and childs using either the XMPP4R's helpers
# or directly using REXML's methods.
#
# ===Automatic element casting
#
# Because there are special classes derived from REXML::Element to ease
# development on the protocol level, Elements must be cast to them. This is
# done via REXML::Element.import. This method is also used in import class
# methods of some Element classes.
#
# The first occurance of this feature is in Jabber::Stream::receive:
# * <tt><message/></tt> stanzas are cast to Jabber::Message class
# * <tt><presence/></tt> stanzas are cast to Jabber::Presence class
# * <tt><iq/></tt> stanzas are cast to Jabber::Iq class
#
# This is not only useful for stanzas but all other XML processing, too:
# * <tt><x/></tt> children elements of <tt><message/></tt> and <tt><presence/></tt> are converted to Jabber::X
# * <tt><error/></tt> children elements of all three stanzas are converted to Jabber::ErrorResponse
# * <tt><query/></tt> children elements of <tt><iq/></tt> are converted to Jabber::IqQuery
# * <tt><vCard/></tt> children elements of <tt><iq/></tt> are converted to Jabber::IqVcard
#
# The following conversion facilities are only executed if the respective
# library parts are loaded. See below for more details on Non-basic features.
# * Jabber::IqQuery elements are converted to Jabber::Roster::IqQueryRoster if their
#   namespace is 'jabber:iq:roster'
# * Jabber::IqQuery elements are converted to Jabber::Version::IqQueryVersion if their
#   namespace is 'jabber:iq:version'
# * Jabber::IqQuery elements are converted to Jabber::Discovery::IqQueryDiscoInfo if their
#   namespace is 'http://jabber.org/protocol/disco#info'
# * Jabber::IqQuery elements are converted to Jabber::Discovery::IqQueryDiscoItems if their
#   namespace is 'http://jabber.org/protocol/disco#items'
# * <tt><item/></tt> children elements of Jabber::Roster::IqQueryRoster are converted
#   to Jabber::Roster::RosterItem
# * <tt><identity/></tt> children elements of Jabber::IqQueryDiscoInfo are converted
#   to Jabber::Discovery::DiscoIdentity
# * <tt><feature/></tt> children elements of Jabber::IqQueryDiscoInfo are converted
#   to Jabber::Discovery::DiscoFeature
# * <tt><item/></tt> children elements of Jabber::IqQueryDiscoItems are converted
#   to Jabber::Discovery::DiscoItem
#
# To use this, don't check for:
# <tt>iq.queryns == 'http://jabber.org/protocol/disco#info'</tt>
#
# But instead check for the query's class:
# <tt>iq.query.kind_of?(Jabber::IqQueryDiscoInfo)</tt>
#
# ==Where to begin?
#
# Because it is built in an extensible way, it might be hard for newcomers to
# understand where to look at documentation for a specific method. For example,
# Client inherits from Connection, which itself inherits from Stream.
#
# A newcomer should have a look at the <tt>Jabber::Client</tt> and
# <tt>Jabber::Component</tt> classes, and their parent classes
# <tt>Jabber::Connection</tt> and <tt>Jabber::Stream</tt>.  The best way to
# understand how to use them is probably to look at the examples in the
# <tt>examples/</tt> dir.
#
# ==Non-basic features
#
# <tt>require 'xmpp4r'</tt> only includes basic functionality for
# Connections, Authentication, Stream processing, Callbacks, Stanza handling
# and Debugging to keep the library's footprint small.
#
# There is code for features that aren't required by a *basic* client. These
# must be additionally included to use them.
#
# ===Protocol-level features
#
# You're highly advised to read the according RFCs and JEPs if you intend to
# use them. The benefit will be that you'll understand the protocols and be
# going to be more efficient when programming with them.
#
# * Jabber::Bytestreams, Jabber::FileTransfer: <tt>require 'xmpp4r/bytestreams'</tt>
# * Jabber::Dataforms: <tt>require 'xmpp4r/dataforms'</tt>
# * Jabber::Delay: <tt>require 'xmpp4r/delay'</tt>
# * Jabber::Discovery: <tt>require 'xmpp4r/discovery'</tt>
# * Jabber::FeatureNegotiation: <tt>require 'xmpp4r/feature_negotiation'</tt>
# * Jabber::MUC: <tt>require 'xmpp4r/muc'</tt>
# * Jabber::Roster: <tt>require 'xmpp4r/roster'</tt>
# * Jabber::Vcard: <tt>require 'xmpp4r/vcard'</tt>
# * Jabber::Version: <tt>require 'xmpp4r/version'</tt>
#
# ===Helpers
#
# Helpers are intended to give more simplistic interfaces to various tasks
# of Jabber clients at the cost of flexibility. But you won't need that
# level of flexibility in most cases.
#
# * Jabber::Roster::Helper: <tt>require 'xmpp4r/roster'</tt>
# * Jabber::MUC::MUCBrowser, Jabber::MUC::MUCClient, Jabber::MUC::SimpleMUCClient: <tt>require 'xmpp4r/muc'</tt>
# * Jabber::Version::SimpleResponder, Jabber::Version::Responder: <tt>require 'xmpp4r/version'</tt>
# * Jabber::Vcard::Helper: <tt>require 'xmpp4r/vcard'</tt>
# * Jabber::FileTransfer::Helper, Jabber::Bytestreams::SOCKS5BytestreamsServer: <tt>require 'xmpp4r/bytestreams'</tt>
#
# ==Debugging
#
# Dumping your Jabber stream can be enabled this way:
#   Jabber::debug = true

require 'xmpp4r/xmpp4r'
