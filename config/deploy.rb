set :application, "drupal6_sandbox"
set :use_sudo, false
set :default_stage, "staging"

# To set other stuff use environment related files, i.e.
# deploy/staging.rb or deploy/production.rb

set :asset_folders, %W(files)

namespace :deploy do
  desc "Deploy the Drupal"
  task :default do
    update
    deploy.customize
  end

  desc "Setup a GitHub-style deployment."
  task :setup, :except => { :no_release => true } do
    run "git clone #{repository} #{current_path}"
    asset_folders.each do |asset|
      run "mkdir -p #{shared_path}/assets/#{asset}"
    end
    run "echo '0 * * * *  #{current_path}/drush/drush.php --root=#{current_path}/drupal cron > /dev/null 2>&1' >> #{home_dir}/crontab.conf"
    run "crontab #{home_dir}/crontab.conf" # Apply
  end

  desc "Update the deployed code."
  task :update_code, :except => { :no_release => true } do
    run "cd #{current_path}; git fetch origin; git reset --hard origin/#{branch}; git submodule init && git submodule update"
  end

  namespace :rollback do
    desc "Rollback a single commit."
    task :code, :except => { :no_release => true } do
      set :branch, "HEAD^"
      deploy.default
    end

    task :default do
      rollback.code
    end
  end

  desc "Override deploy:symlink task"
  task :symlink, :except => { :no_release => true } do
    asset_folders.each do |asset|
      run "rm -rf #{current_path}/sites/default/#{asset}"
      run "ln -nfs #{shared_path}/assets/#{asset} #{current_path}/sites/default/#{asset}"
    end
  end

  desc <<-DESC
    All custom tasks will be here
  DESC
  task :customize, :except => { :no_release => true } do
    # custom tasks
    stamp = Time.now.utc.strftime("%Y%m%d%H%M.%S")
    theme_asset_paths = %w(images css).map { |p| "#{current_path}/sites/all/themes/*/#{p}" }.join(" ")
    run "find #{theme_asset_paths} -exec touch -t #{stamp} {} ';'; true", :env => { "TZ" => "UTC" }
  end
end
