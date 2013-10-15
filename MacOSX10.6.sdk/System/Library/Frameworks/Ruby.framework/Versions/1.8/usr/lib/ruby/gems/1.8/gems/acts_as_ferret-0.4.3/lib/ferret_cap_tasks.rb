# Ferret DRb server Capistrano tasks
# Usage:
# Add require 'vendor/plugins/acts_as_ferret/lib/ferret_cap_tasks' to your
# config/deploy.rb
# call ferret.restart where you restart your Mongrels.
# ferret.stop and ferret.start are available, too.
module FerretCapTasks
  def start
    run "cd #{current_path}; RAILS_ENV=production script/ferret_start"
  end

  def stop
    run "cd #{current_path}; RAILS_ENV=production script/ferret_stop"
  end

  def restart
    stop
    start
  end
end
Capistrano.plugin :ferret, FerretCapTasks
