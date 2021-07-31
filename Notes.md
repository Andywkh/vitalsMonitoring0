# Install Packages within a virtual env so as to enable easier work environments using same package versioning 
pip3 install virtualenv

# Creating the virtual env "env" and activate it
virtualenv env
source env/bin/activate

pip3 install flask flask-sqlalchemy

# Within the vitals_monitoring folder, create a sub_folder to separate the python pip files from the api codes
# you then export the flask app to be an api, allowing you to use flask run on whatever is within the API
export FLASK_APP=api
export FLASK_DEBUG=1 

flask run --host=0.0.0.0

# Create your DB
python
from api.models import Vital
from api import db, create_app
db.create_all(app=create_app())

# To query your db
sqlite3 api/database.db 
select * from vital;
DELETE FROM vital;

# ------------------------------------- React ------------------------------------
# Check your node and npx package versioning, if you dont have it on your on-prem, download it within your venv
node -v
npx --version

# add your symentic UI react to integrate your css files into react components, 
# Note: in your virtual env, cd into frontend folder
yarn add semantic-ui-react
yarn add semantic-ui-css

# create a proxy under package.json, to avoid cors problems
"proxy": "http://localhost:5000",