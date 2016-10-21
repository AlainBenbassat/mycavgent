<?php

class MyCavariaOrganization {
  public $id;
  public $hash;
  public $name = '';
  public $street = '';
  public $addressLine1 = '';
  public $addressLine2 = '';
  public $postalCode = '';
  public $city = '';

  public function __construct($id) {
    // get the contact
    $contact = civicrm_api3('Contact', 'getsingle', array(
      'id' => $id,
      'contact_type' => 'Organization',
      'return' => 'id,hash,display_name,street_address,supplemental_address_1,supplemental_address_2,postal_code,city',
    ));

    $this->id = $contact['id'];
    $this->hash = $contact['hash'];
    $this->name = $contact['display_name'];
    $this->street = $contact['street_address'];
    $this->addressLine1 = $contact['supplemental_address_1'];
    $this->addressLine2 = $contact['supplemental_address_2'];
    $this->postalCode = $contact['postal_code'];
    $this->city = $contact['city'];
  }

  public function update($newValues) {

  }
}