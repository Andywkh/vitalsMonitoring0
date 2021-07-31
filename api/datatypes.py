from . import db 

'''Setting up your typing for your ingested data'''
class Vital(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    patient_ID = db.Column(db.Integer)
    time = db.Column(db.String(25))
    temperature = db.Column(db.String(5))
    heartbeat = db.Column(db.String(5))