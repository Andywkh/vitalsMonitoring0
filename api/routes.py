from flask import Blueprint, jsonify, request
from . import db 
from .datatypes import Vital

from datetime import datetime

main = Blueprint('main', __name__)

"""To add data into database via a http post request"""
@main.route('/add_vital', methods=['POST'])
def add_vital():
    vital_data = request.get_json()
    now = datetime.now()
    
    new_vital = Vital(patient_ID=vital_data['patientID'], 
                time = now.strftime("%m/%d/%Y, %H:%M:%S"),
                temperature=vital_data['temp'], 
                heartbeat=vital_data['heartbeat'])

    db.session.add(new_vital)
    db.session.commit()

    return 'Done', 201

"""To query data from database by initiating a list, ingesting data into the list, and reading the list"""
@main.route('/vitals')
def vitals():
    vital_list = Vital.query.all()
    vitals = []

    for vital in vital_list:
        vitals.append({'patientID' : vital.patient_ID, 'time' : vital.time, 'temp' : vital.temperature, 'heartbeat' : vital.heartbeat})

    return jsonify({'vitals' : vitals[::-1]})

'''
return jsonify({'vitals' : vitals})
'''