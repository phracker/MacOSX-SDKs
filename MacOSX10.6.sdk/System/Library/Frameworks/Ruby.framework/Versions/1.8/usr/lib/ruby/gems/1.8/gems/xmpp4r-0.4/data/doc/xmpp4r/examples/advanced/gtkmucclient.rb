#!/usr/bin/env ruby

require 'gtk2'

$:.unshift '../../../../../lib'
require 'xmpp4r'
require 'xmpp4r/muc/helper/simplemucclient'
require 'xmpp4r/version/helper/simpleresponder'

#Jabber::debug = true

class Gtk::Label
  def self.new_show(str = nil, mnemonic = false)
    label = new(str, mnemonic)
    label.show
    label
  end
end

class SetupWindow < Gtk::Window
  def initialize
    super(Gtk::Window::TOPLEVEL)
    self.title = "GtkMUCClient setup"
    signal_connect("delete_event") { cancel }

    vbox = Gtk::VBox.new
    vbox.set_border_width(4)
    add(vbox)
    vbox.show

    frame1 = Gtk::Frame.new('Jabber Account Settings')
    frame1.set_border_width(4)
    frame1.show
    vbox.add(frame1)

    layout1 = Gtk::Table.new(4, 2)
    layout1.row_spacings = 4
    layout1.column_spacings = 8
    layout1.show
    frame1.add(layout1)

    layout1.attach(Gtk::Label.new_show('Jabber ID:'), 0, 1, 1, 2)
    @entry_jid = Gtk::Entry.new
    @entry_jid.text = 'collector@jabber.ccc.de'
    @entry_jid.show
    layout1.attach(@entry_jid, 1, 2, 1, 2)

    layout1.attach(Gtk::Label.new_show('Password:'), 0, 1, 2, 3)
    @entry_password = Gtk::Entry.new
    @entry_password.visibility = false
    @entry_password.show
    layout1.attach(@entry_password, 1, 2, 2, 3)

    layout1.attach(Gtk::Label.new_show('Resource:'), 0, 1, 3, 4)
    @entry_resource = Gtk::Entry.new
    @entry_resource.text = 'gtkmucclient'
    @entry_resource.show
    layout1.attach(@entry_resource, 1, 2, 3, 4)


    frame2 = Gtk::Frame.new('Multi-User Chat Settings')
    frame2.set_border_width(4)
    frame2.show
    vbox.add(frame2)

    layout2 = Gtk::Table.new(3, 2)
    layout2.row_spacings = 4
    layout2.column_spacings = 8
    layout2.show
    frame2.add(layout2)

    layout2.attach(Gtk::Label.new_show('Room:'), 0, 1, 1, 2)
    @entry_room = Gtk::Entry.new
    @entry_room.text = 'test@conference.jabber.org'
    @entry_room.show
    layout2.attach(@entry_room, 1, 2, 1, 2)

    layout2.attach(Gtk::Label.new_show('Nick:'), 0, 1, 2, 3)
    @entry_nick = Gtk::Entry.new
    @entry_nick.text = 'XMPP4R-Fan'
    @entry_nick.show
    layout2.attach(@entry_nick, 1, 2, 2, 3)


    hbox = Gtk::HBox.new
    hbox.show
    vbox.add(hbox)

    button_ok = Gtk::Button.new("Ok")
    button_ok.set_border_width(4)
    hbox.add(button_ok)
    button_ok.signal_connect("clicked") { ok }
    button_ok.can_default = true
    button_ok.grab_default
    button_ok.show
    button_cancel = Gtk::Button.new("Cancel")
    button_cancel.set_border_width(4)
    hbox.add(button_cancel)
    button_cancel.signal_connect("clicked") { cancel }
    button_cancel.show
  end

  def error_dialog(msg)
    dialog = Gtk::MessageDialog.new(self, Gtk::Dialog::MODAL, Gtk::MessageDialog::ERROR, Gtk::MessageDialog::BUTTONS_OK, msg)
    dialog.signal_connect("response") { dialog.destroy }
    dialog.run
  end

  def ok
    jid = Jabber::JID.new(@entry_jid.text)
    mucjid = Jabber::JID.new(@entry_room.text)

    if jid.node.nil?
      error_dialog("Your Jabber ID must contain a user name and therefore contain one @ character.")
    elsif jid.resource
      error_dialog("If you intend to set a custom resource, put that in the right text field. Remove the slash!")
    elsif @entry_resource.text.empty?
      error_dialog("Please set a resource. This is a somewhat unimportant setting...")
    elsif mucjid.node.nil?
      error_dialog("Please set a room name, e.g. myroom@conference.jabber.org")
    elsif mucjid.resource
      error_dialog("The MUC room must not contain a resource. Remove the slash!")
    elsif @entry_nick.text.empty?
      error_dialog("Please set a nick for MUC.")
    else
      jid.resource = @entry_resource.text
      mucjid.resource = @entry_nick.text
      password = @entry_password.text

      destroy

      ChatWindow.new(jid, password, mucjid).show
    end
  end

  def cancel
    destroy
    Gtk.main_quit
  end
end

class ChatWindow < Gtk::Window
  def initialize(jid, password, mucjid)
    super(Gtk::Window::TOPLEVEL)
    self.title = "GtkMUCClient: #{mucjid.resource} in #{mucjid.strip}"
    signal_connect("delete_event") { destroy; Gtk.main_quit }

    layout = Gtk::VBox.new

    @topic = Gtk::Entry.new
    @topic.editable = false
    @topic.show
    layout.pack_start(@topic, false, false, 2)

    layout_mid = Gtk::HPaned.new
    layout_mid.position = 500
    layout_mid.show
    layout.pack_start(layout_mid)

    @buffer_scroll = Gtk::ScrolledWindow.new
    @buffer_scroll.show
    @buffer_scroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC)
    layout_mid.pack1(@buffer_scroll, true, true)

    @buffer_view = Gtk::TextView.new
    @buffer_view.editable = false
    @buffer_view.cursor_visible = false
    @buffer_view.wrap_mode = Gtk::TextTag::WRAP_WORD
    @buffer_view.modify_font(Pango::FontDescription.new('monospace 12'))
    @buffer_view.show
    @buffer_scroll.add_with_viewport(@buffer_view)

    roster_scroll = Gtk::ScrolledWindow.new
    roster_scroll.show
    roster_scroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC)
    layout_mid.pack2(roster_scroll, true, true)

    @roster = Gtk::ListStore.new(String)
    @roster.set_sort_column_id(0)
    roster_view = Gtk::TreeView.new(@roster)
    roster_view.append_column Gtk::TreeViewColumn.new("Participant", Gtk::CellRendererText.new, {:text => 0})
    roster_view.show
    roster_scroll.add_with_viewport(roster_view)

    @input = Gtk::Entry.new
    @input.grab_focus
    @input.signal_connect("activate") {
      on_input(@input.text)
      @input.text = ''
    }
    @input.show
    layout.pack_start(@input, false, false, 2)

    layout.show
    add(layout)

    print_buffer "Welcome to the XMPP4R sample GTK2 Multi-User Chat client"
    print_buffer "Commands start with a slash, type \"/help\" for a list"

    @client = Jabber::Client.new(jid)
    Jabber::Version::SimpleResponder.new(@client, "XMPP4R example: GtkMUCClient", Jabber::XMPP4R_VERSION, IO.popen("uname -sr").readlines.to_s.strip)
    Thread.new {
      begin
        print_buffer "Connecting for domain #{jid.domain}..."
        @client.connect
        print_buffer "Authenticating for #{jid.strip}..."
        @client.auth(password)
        print_buffer "Attempting to join #{mucjid.strip} as #{mucjid.resource}..."
        @muc = Jabber::MUC::SimpleMUCClient.new(@client)
        register_handlers
        @muc.join(mucjid)
      rescue Exception => e
        puts "#{e.class}: #{e}\n#{e.backtrace.join("\n")}"
        print_buffer("Error: #{e}")
      end
    }

    set_size_request(600, 400)
  end

  def print_buffer(s, time=nil)
    @buffer_view.buffer.insert(@buffer_view.buffer.end_iter, "[#{(time || Time.new).getlocal.strftime('%I:%M')}] #{s}\n")
    va = @buffer_scroll.vadjustment
    va.value = va.upper
  end

  def register_handlers
    @muc.on_room_message { |time,text|
      print_buffer("*** #{text}", time)
    }
    @muc.on_message { |time,nick,text|
      if text =~ /^\/me (.+)$/
        print_buffer("*#{nick} #{$1}", time)
      else
        print_buffer("<#{nick}> #{text}", time)
      end
    }
    @muc.on_private_message { |time,nick,text|
      print_buffer("<-(#{nick}) #{text}", time)
    }
    @muc.on_join { |time,nick|
      @roster.append[0] = nick
    }
    @muc.on_self_leave { |time|
      print_buffer("You have exited the room", time)
    }
    @muc.on_leave { |time,nick|
      del_iter = nil
      @roster.each { |m,p,iter|
        del_iter = iter if iter[0] == nick
      }
      @roster.remove(del_iter) if del_iter
    }
    @muc.on_subject { |time,nick,subject|
      @topic.text = subject
    }
  end

  def on_input(line)
    commands = {
      'help' => [
        'Display this help',
        lambda {
          commands.each { |cmd,a|
            print_buffer "/#{cmd.ljust(10)} - #{a[0]}"
          }
        }
      ],
      'msg' => [
        'Send a private message to a user',
        lambda { |args|
          # Limitation: it is not possible to send private messages
          # to a user with a space in his nickname
          to = args.shift
          text = args.join(' ')
          @muc.say(text, to)
          print_buffer "->(#{to}) #{text}"
        }
      ],
      'subject' => [
        'Change the room\'s subject',
        lambda { |args|
          @muc.subject = args.join(' ')
        }
      ],
      'quit' => [
        'Leave room with optional message, then disconnect client and shut down',
        lambda { |args|
          @muc.exit(args.join(' ')) if @muc.active?
          @client.close
          Gtk.main_quit
        }
      ]
    }

    if line =~ /^\//
      args = line.split(/ /)
      cmd = args.shift[1..-1].downcase

      command = commands[cmd]
      if command
        help, func = command
        func.call(args)
      else
        print_buffer "Unknown command: #{cmd}, use \"/help\""
      end
    else
      @muc.say(line)
    end
  end
end

Gtk.init
SetupWindow.new.show
Gtk.main
