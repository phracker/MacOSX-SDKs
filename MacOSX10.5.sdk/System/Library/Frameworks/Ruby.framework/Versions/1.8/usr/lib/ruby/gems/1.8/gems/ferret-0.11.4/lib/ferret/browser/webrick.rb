module WEBrick
  class FerretBrowserHandler < WEBrick::HTTPServlet::AbstractServlet
    # Creates a FerretBrowserHandler, which answers for the application
    # within +klass+.
    def initialize(server, reader, path)
        super(server)
        @delegator = Ferret::Browser::Delegator.new(reader, path)
    end
    # Handler for WEBrick requests (also aliased as do_POST).
    def do_GET(req, res)
      res.status, res.content_type, res.body = @delegator.run(req.meta_vars)
    end
  end
end
