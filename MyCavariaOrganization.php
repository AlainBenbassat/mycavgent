<?php

class MyCavariaOrganization {
  public $id = -1;
  public $hash = -1;
  public $name = '';
  public $addressID = -1;
  public $street = '';
  public $addressLine1 = '';
  public $addressLine2 = '';
  public $postalCode = '';
  public $city = '';

  public function __construct($id = NULL) {
    if (!empty($id)) {
      $this->load($id);
    }
  }

  public function load($id) {
    // get the contact
    $contact = civicrm_api3('Contact', 'getsingle', array(
      'id' => $id,
      'contact_type' => 'Organization',
      'return' => 'id,hash,display_name,address_id,street_address,supplemental_address_1,supplemental_address_2,postal_code,city',
    ));

    $this->id = $contact['id'];
    $this->hash = $contact['hash'];
    $this->name = $contact['display_name'];
    $this->addressID = $contact['address_id'];
    $this->street = $contact['street_address'];
    $this->addressLine1 = $contact['supplemental_address_1'];
    $this->addressLine2 = $contact['supplemental_address_2'];
    $this->postalCode = $contact['postal_code'];
    $this->city = $contact['city'];
  }

  public function update($newValues) {
    // make sure id and hash match
    if ($newValues['a'] != $this->id || $newValues['b'] != $this->hash) {
      throw new Exception('Kan de gegevens de organisatie niet bewaren. Foutcode = 1.');
    }

    // update the organization
    $params = array(
      'id' => $newValues[a],
      'api.address.create' => array(
        'id' => $this->addressID,
        'street_address' => $newValues['street'],
        'supplemental_address_1' => $newValues['addressLine1'],
        'supplemental_address_2' => $newValues['addressLine2'],
        'postal_code' => $newValues['postalCode'],
        'city' => $newValues['city'],
      ),
    );
    $contact = civicrm_api3('Contact', 'create', $params);

    // reload
    $this->load($newValues['a']);
  }
}